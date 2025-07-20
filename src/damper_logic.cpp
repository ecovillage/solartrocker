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

const int		time_dehydrating = 2 * 60; // Sekunden
unsigned long	timestamp_dehydrating = 0;
const int		time_heating = 5 * 60; // Sekunden
unsigned long	timestamp_heating = 0;
const float		min_percent_change_hydr = 5;
float			temp_start_heating;
unsigned long	timestamp_auto = 0;
unsigned long	timestamp_state_menue = 0;
unsigned long	timestamp_state_RF_const = 0;
const int		time_state_menue = 0.5 * 60; // Sekunden
int 			state = 0;
int				last_state = 0;

void state_menue()
{
	show_menue();
	if (timestamp_now_s() - timestamp_state_menue > time_state_menue)
	{
		set_state(last_state);
	}
	set_time_LCD(time_state_menue - (timestamp_now_s() - timestamp_state_menue));
}

void set_state(int nb)
{
	last_state = state;
	state = nb;
}

void set_state_auto()
{
	set_state(0);
	set_text_state("auto");
	timestamp_auto = timestamp_now_s();
}

void set_state_lueften()
{
	set_state(1);
	set_text_state("Lueften");
	timestamp_dehydrating = timestamp_now_s();
}

void set_state_heizen()
{
	set_state(2);
	set_text_state("Heizen");
	timestamp_heating = timestamp_now_s();
	temp_start_heating = read_bme_temperature();
}

void set_state_RF_const()
{
	set_state(3);
	set_text_state("RF konst");
	timestamp_state_RF_const = timestamp_now_s();
}

void set_state_menue()
{
	set_state(4);
	set_text_state("Menue");
	timestamp_auto = timestamp_now_s();
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
	else if (air_humidity_inside > (127.68 - 2.80 * air_temperature_inside + 0.0192 * air_temperature_inside * air_temperature_inside)) //(117.68 - 2.80 * air_temperature_inside + 0.0192 * air_temperature_inside * air_temperature_inside)
		return (true);
	return (false);
}

unsigned long timestamp_now_s(void)
{
	return (millis()/1000);
}

void state_auto()
{
	if (air_too_moist(read_bme_humidity(),read_bme_temperature()))
	{
		set_state_lueften();
		return ;
	}
	else if (is_hydrating_const())
	{
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
		set_state_heizen();
	}
	set_time_LCD(time_dehydrating - (timestamp_now_s() - timestamp_dehydrating));	
}

void state_heating()
{
	close_damper();
	fan_on();
	if (read_bme_temperature() - temp_start_heating > 1)
	{
		timestamp_heating = timestamp_now_s();
		temp_start_heating = read_bme_temperature();
	}
	if (timestamp_now_s() - timestamp_heating > time_heating)
	{
		set_state_auto();
	}
	set_time_LCD(time_heating - (timestamp_now_s() - timestamp_heating));
}

bool is_hydrating_const()
{
	float	delta;

	delta = delta_min_max_humidity_bme();
	if (delta < min_percent_change_hydr)
		return (true);
	else
		return (false);
}

void state_RF_const()
{
	if (is_hydrating_const())
	{
		if (read_bme_temperature() > read_temp(0) + 5)
			set_state_lueften();
		else
			fan_off();
	}
	else
		set_state_auto();
	set_time_LCD(timestamp_now_s() - timestamp_state_RF_const);
}

// void check_fan_neccessary()
// {
// 	float	delta;

// 	delta = delta_min_max_humidity_bme();
// 	if (delta < min_percent_change_hydr)
// 	{	
// 		fan_off();
// 		set_text_state("RF zu konst");
// 	}
// 	else
// 		fan_on();
// 		clear_text_state();
// }
