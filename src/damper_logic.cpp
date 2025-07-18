#include "Arduino.h"
#include "damper_logic.h"
#include "damper.h"
#include "bme280.h"
#include "fan.h"
#include "data.h"
#include "lcd.h"
#include "display.h"

const int		time_dehydrating = 180; // Sekunden
const int		time_block_dehydrating = 300 + time_dehydrating; // Sekunden
unsigned long	timestamp_dehydrating = 0;
const float		min_percent_change_hydr = 0.5;

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

void check_hydrating()
{
	if (!(timestamp_now_s() - timestamp_dehydrating < time_dehydrating)) // not (81258 - 81250 = 8 < 180)
	{
		if (!(timestamp_now_s() - timestamp_dehydrating < time_block_dehydrating))  // check air_too_moist aussetzen damit ausgetauschte Luft sich erwährmen und Feuchte aufnehmen kann.
		{
			if (air_too_moist(read_bme_humidity(),read_bme_temperature()))
			{
				Serial.println("Luftfeuchte zu hoch, öffne Klappen, schalte Fan an");
				fan_on();
				open_damper();
				timestamp_dehydrating = timestamp_now_s();
				set_text_status("Lueften");
			}
			else
			{
				close_damper();
				Serial.println("Luftfeuchte ok");
				Serial.println(timestamp_now_s() - timestamp_dehydrating);
				set_text_status("ok");
				check_fan_neccessary();
			}
		}
		else
		{
			set_text_status("Luef. block");
		}
	}
	else
	{
		set_text_status("Lueften");
		Serial.print("Modus: Lüften noch (s): ");
		Serial.println(time_dehydrating - timestamp_now_s() - timestamp_dehydrating);
	}
}

void check_fan_neccessary()
{
	float	delta;

	delta = delta_min_max_humidity_bme();
	Serial.print("delta max min humidity: ");
	Serial.println(delta);
	if (delta < min_percent_change_hydr)
	{	
		Serial.println("Luftfeuchte zu konstant, schalte Fan aus");
		fan_off();
		set_text_status("RF zu konst");
	}
	else
		fan_on();
		clear_text_status();
}

void print_time_lueften()
{
	if (timestamp_now_s() - timestamp_dehydrating < time_dehydrating)
	{
		print_str_lcd("Restzeit L: ");
		print_int_lcd(time_dehydrating - (timestamp_now_s() - timestamp_dehydrating));
		print_str_lcd(" s");
		print_str_lcd("\n");
	}
}
