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
#include <Wire.h>
#include "sht3x.h"

void setup()
{
	Serial1.begin(9600);
	Wire.begin();
	delay(1000);
	BME280_setup();
	SHT3X_setup();
	fan_setup();
	damper_setup();
	lcd_setup();
	buttons_setup();
	data_setup();
	set_state_auto();
}

void loop()
{
	if (button1_pressed())
	{
		set_state_menue();
	}
	if (get_state() == 0)
		state_auto();
	else if (get_state() == 1)
		state_dehydrating();
	else if (get_state() == 2)
		state_heating();
	else if (get_state() == 3)
		state_RF_const();
	else if (get_state() == 4)
		state_menue();
	save_max_temp();
	display();
	collect_data();
	delay(300);
}
