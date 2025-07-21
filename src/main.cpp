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

void setup()
{
	Serial.begin(9600);
	Serial.println("Starte Solartrockner!");
	fan_setup();
	BME280_setup();
	damper_setup();
	lcd_setup();
	buttons_setup();
	Wire.begin();
	set_state(0);
	show_logo();
}

void loop()
{
	if (button1_pressed())
	{
		set_state(4);
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
	{
		state_menue();
		return ;
	}
	save_max_temp();
	show_values();
	collect_data();
	delay(100);
}
