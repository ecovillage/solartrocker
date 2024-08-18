#include "Arduino.h"
#include "damper_logic.h"
#include "damper.h"
#include "bme280.h"
#include "fan.h"
#include "data.h"

const size_t	HUMIDITY    = 0;
const size_t	TEMPERATURE = 1;
int 			timestamp_dehydrating;
int				time_dehydrating = 1000; //60 * 1000; // 1min
int				min_percent_change_hydr = 10;

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
	else if (air_humidity_inside > (117.68 - 2.80 * air_temperature_inside + 0.0192 * air_temperature_inside * air_temperature_inside))
		return (true);
	return (false);
}

boolean check_humidity()
{
	if (!(timestamp_dehydrating - millis() < time_dehydrating))
	{
		close_damper();
		if (air_too_moist(read_bme_humidity(),read_bme_temperature()))
		{
			fan_on();
			open_damper();
			timestamp_dehydrating = millis();
			return (true);
		}
		return (false);
	}
	return (true);
}

void check_fan_neccessary()
{
	if (read_bme_humidity() - avarage_humidity_bme() < min_percent_change_hydr && (read_bme_humidity() - avarage_humidity_bme()) * -1  < min_percent_change_hydr)
		fan_off();
}