#include <Arduino.h>
#include "fan.h"
#include "damper.h"
#include "lcd.h"
#include "bme280.h"
#include "display.h"
#include "ds18B20.h"
#include "buttons.h"
#include "storage.h"
#include "data.h"
#include "damper_logic.h"

void setup()
{	
	Serial.begin(9600);
	fan_setup();
	BME280_setup();
	damper_setup();
	lcd_setup();
	buttons_setup();
}

void loop()
{
	if (button1_pressed())
	{
		open_damper();
		delay(200);
		return ;
	}
	if (button2_pressed() )
	{
		if (fan_state() == 0)
			fan_on();
		else
			fan_off();
		delay(200);
		return ;
	}
	if (button3_pressed())
	{
		set_modus(read_modus() + 1);
		reset_max_temp();
		delay(200);
	}
	if (!check_humidity())
		check_fan_neccessary();
	save_max_temp();
	display_values();
	collect_data();
	delay(100);
}
