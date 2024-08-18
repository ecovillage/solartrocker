#include "Arduino.h"
#include "damper_logic.h"
#include "damper.h"
#include "bme280.h"
#include "fan.h"
#include "data.h"

const size_t	HUMIDITY    = 0;
const size_t	TEMPERATURE = 1;
const int		time_dehydrating = 60; // 1min
unsigned long	timestamp_dehydrating = -time_dehydrating;
const int		min_percent_change_hydr = 10;

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

boolean check_humidity()
{
	if (!(millis()/1000 - timestamp_dehydrating < time_dehydrating))
	{
		close_damper();
		if (air_too_moist(read_bme_humidity(),read_bme_temperature()))
		{
			Serial.println("Luftfeuchte zu hoch, öffne Klappen, schalte Fan an");
			fan_on();
			open_damper();
			timestamp_dehydrating = millis() / 1000;
			return (true);
		}
		else
			Serial.println("Luftfeuchte ok");
		return (false);
	}
	else
	{
		Serial.print("Modus: Lüften noch (s): ");
		Serial.println(time_dehydrating - (millis()/1000 - timestamp_dehydrating));
		return (true);
	}
}

void check_fan_neccessary()
{
	
	if (delta_min_max_humidity_bme() < min_percent_change_hydr)
	{	
		Serial.println("Luftfeuchte zu konstant, schalte Fan aus");
		fan_off();
	}
}