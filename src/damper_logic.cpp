#include "Arduino.h"
#include "damper_logic.h"
#include "damper.h"
#include "bme280.h"
#include "fan.h"
#include "data.h"
#include "lcd.h"
#include "display.h"
#include "buttons.h"
#include "storage.h"
#include "ds18B20.h"
#include "menue.h"
#include "sht3x.h"

const int		time_dehydrating = 2 * 60; // Sekunden, 2 = Erkenntnis wann Feuchte_abs_innen = Feuchte_abs_aussen
unsigned long	timestamp_dehydrating = 0;
const int		time_heating = 5 * 60; // Sekunden
unsigned long	timestamp_heating = 0;
const float		min_change_hydr = 2;
float			temp_start_heating;
unsigned long	timestamp_auto = 0;
unsigned long	timestamp_state_RF_const = 0;
unsigned long	timestamp_manuel = 0;
unsigned long	timestamp_night = 0;
int 			state = 0;
int				last_state = 0;

void set_state(int nb)
{
	last_state = state;
	state = nb;
}

void set_state_manuel()
{
	set_state(Manuel);
	set_modus_display(Display_Values);
	set_text_state("manuell");
	timestamp_manuel = timestamp_now_s();
}

void set_state_auto()
{
	set_state(Auto);
	set_modus_display(Display_Values);
	set_text_state("automatik");
	timestamp_auto = timestamp_now_s();
}

void set_state_lueften()
{
	set_state(Lueften);
	set_modus_display(Display_Values);
	set_text_state("Lueften");
	timestamp_dehydrating = timestamp_now_s();
}

void set_state_heizen()
{
	set_state(Heizen);
	set_modus_display(Display_Values);
	set_text_state("Heizen");
	timestamp_heating = timestamp_now_s();
	temp_start_heating = read_innen_temperature();
}

void set_state_RF_const()
{
	set_state(RF_const);
	set_modus_display(Display_Values);
	set_text_state("RF konst");
	timestamp_state_RF_const = timestamp_now_s();
}

void set_state_night()
{
	set_state(Night);
	set_modus_display(Display_Values);
	set_text_state("Nacht-Mod");
	timestamp_night = timestamp_now_s();
}

int get_state()
{
	return (state);
}

/** Check whether we are on the "right" side of the curve.      */
bool air_too_moist(float air_humidity_inside, float air_temperature_inside) {
  // moisture vs temperature, stay below to keep heating
  
	if (air_temperature_inside > 80)
	{
		if (air_humidity_inside > 18)
			return (true);
		else
			return (false);
	}
	else if (air_temperature_inside < 15)
	{
		if (air_humidity_inside > 80)
			return (true);
		else
			return (false);
	}
	else if (air_humidity_inside > (117.68 - 2.80 * air_temperature_inside + 0.0192 * air_temperature_inside * air_temperature_inside)) //(117.68 - 2.80 * air_temperature_inside + 0.0192 * air_temperature_inside * air_temperature_inside)
		return (true);
	return (false);
}

unsigned long timestamp_now_s(void)
{
	return (millis()/1000);
}

void state_auto()
{
	if (is_day() == false)
	{
		set_infotext("is_day() == false");
		set_state_night();
		return ;
	}
	if (air_too_moist(read_innen_humidity(),read_innen_temperature()) && calculateAbsoluteHumidity(read_innen_temperature(), read_innen_humidity()) > calculateAbsoluteHumidity(read_aussen_temperature(), read_aussen_humidity()))
	{
		set_infotext("air_too_moist() && F_abs_innen > F_abs_aussen");
		set_state_lueften();
		return ;
	}
	else if (is_first_round() == false && is_hydrating_const())
	{
		set_infotext("is_hydrating_const() == true");
		set_state_RF_const();
		return ;
	}
	else
	{
		fan_on();
		close_damper();
	}
	set_time_LCD(timestamp_now_s() - timestamp_auto);
}	

void state_dehydrating()
{
	fan_on();
	open_damper();
	if (timestamp_now_s() - timestamp_dehydrating > time_dehydrating)
	{
		set_infotext("Zeit ist um");
		set_state_heizen();
	}
	set_time_LCD(time_dehydrating - (timestamp_now_s() - timestamp_dehydrating));	
}

void state_heating()
{
	close_damper();
	fan_on();
	if (read_innen_temperature() - temp_start_heating > 1)
	{
		timestamp_heating = timestamp_now_s();
		temp_start_heating = read_innen_temperature();
		set_infotext("restart timer Heizen");
	}
	if (timestamp_now_s() - timestamp_heating > time_heating)
	{
		set_infotext("Zeit ist um");
		set_state_auto();
	}
	set_time_LCD(time_heating - (timestamp_now_s() - timestamp_heating));
}

bool is_hydrating_const()
{
	return (delta_min_max_abs_humidity() < min_change_hydr);
}

void state_RF_const()
{
	if (is_hydrating_const())
	{
		if (read_innen_temperature() > read_temp(0) + 5)
		{
			set_infotext("read_innen_temperature() > read_temp(0) + 5");
			set_state_lueften();
		}
		else if ((timestamp_now_s() - timestamp_state_RF_const) % (30 * 60) > 29 * 60) //Zeit läuft in einem 30-Minuten-Zyklus. Sobald der Zyklusrest 1740 Sekunden oder mehr ist → Lüfter an
			fan_on();
		else
			fan_off();
	}
	else
	{
		set_infotext("is_hydrating_const() == false");
		set_state_auto();
	}
	set_time_LCD(timestamp_now_s() - timestamp_state_RF_const);
}

void state_manuel()
{
	set_time_LCD(timestamp_now_s() - timestamp_manuel);
}

void state_night()
{
	close_damper();
	if ((timestamp_now_s() - timestamp_night) % (30 * 60) > 29 * 60) //Zeit läuft in einem 30-Minuten-Zyklus. Sobald der Zyklusrest 1740 Sekunden oder mehr ist → Lüfter an
			fan_on();
		else
			fan_off();
	if (is_day() == true && calculateAbsoluteHumidity(read_innen_temperature(), read_innen_humidity()) > calculateAbsoluteHumidity(read_aussen_temperature(), read_aussen_humidity()))
	{
		set_infotext("is_day() == true && F_abs_innen > F_abs_aussen");
		set_state_auto();
		return ;
	}
	set_time_LCD(timestamp_now_s() - timestamp_night);
}