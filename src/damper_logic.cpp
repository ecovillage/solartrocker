#include "Arduino.h"
#include "damper_logic.h"
#include "damper.h"
#include "bme280.h"
#include "fan.h"
#include "data.h"
#include "lcd.h"
#include "display.h"

const int		time_dehydrating = 2 * 60; // Sekunden
unsigned long	timestamp_dehydrating = 0;
const int		time_block_dehydrating = 10 * 60; // Sekunden
unsigned long	timestamp_heating = 0;
const float		min_percent_change_hydr = 0.5;
float			temp_start_heating;
int 			state = 0;

void set_state(int nb)
{
	state = nb;
	if (state == 0)
		set_text_state("auto");
	else if (state == 1)
		set_text_state("Lueften");
	else if (state == 2)
		set_text_state("Heizen");
	else if (state == 3)
		set_text_state("RF konst");
	else if (state == 4)
		set_text_state("manuell");
}

int get_state()
{
	return (state);
}

/** Check whether we are on the "right" side of the curve.      */
boolean air_too_moist(float air_humidity_inside, float air_temperature_inside) {
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
	else if (air_humidity_inside > (117.68 - 2.80 * air_temperature_inside + 0.0192 * air_temperature_inside * air_temperature_inside))
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
		set_state(1);
		timestamp_dehydrating = timestamp_now_s();
		return ;
	}
	else if (is_hydrating_const())
	{
		set_state(3);
		return ;
	}
	else
	{
		fan_on();
		close_damper();
	}
}	

void state_dehydrating()
{
	fan_on();
	open_damper();
	if (timestamp_now_s() - timestamp_dehydrating > time_dehydrating)
	{
		set_state(2);
		timestamp_heating = timestamp_now_s();
		temp_start_heating = read_bme_temperature();
	}
}

void state_heating()
{
	close_damper();
	fan_on();
	if (read_bme_temperature() - temp_start_heating > 1)
		timestamp_heating = timestamp_now_s();
	if (timestamp_now_s() - timestamp_heating > time_block_dehydrating)
		set_state(0);
}

boolean is_hydrating_const()
{
	float	delta;

	delta = delta_min_max_humidity_bme();
	if (delta < min_percent_change_hydr)
		return (true);
	else
		return (false);
}

void state_const_hydrating()
{
	if (is_hydrating_const())
		fan_off();
	else
		set_state(0);
}

void check_fan_neccessary()
{
	float	delta;

	delta = delta_min_max_humidity_bme();
	if (delta < min_percent_change_hydr)
	{	
		fan_off();
		set_text_state("RF zu konst");
	}
	else
		fan_on();
		clear_text_state();
}
