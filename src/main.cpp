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
}

void loop()
{
	if (button1_pressed() || button2_pressed() || button3_pressed())
	{
		set_state(4);
		delay(1000);
	}
	if (get_state() == 0)
		state_auto();
	else if (get_state() == 1)
		state_dehydrating();
	else if (get_state() == 2)
		state_heating();
	else if (get_state() == 3)
		state_const_hydrating();
	else if (get_state() == 4)
		state_manuel();
	save_max_temp();
	display_values();
	collect_data();
	delay(100);
}
