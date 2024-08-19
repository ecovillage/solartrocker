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
		if (damper_state() == 0)
			open_damper();
		else
			close_damper();
		delay(200);
	}
	if (button2_pressed() == 1)
	{
		if (fan_state() == 0)
			fan_on();
		else
			fan_off();
		delay(200);
	}
	if (button3_pressed() == 1)
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
