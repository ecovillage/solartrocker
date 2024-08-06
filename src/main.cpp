#include <Arduino.h>
#include "fan.h"
#include "damper.h"
#include "lcd.h"
#include "bme280.h"
#include "display.h"
#include "ds18B20.h"
#include "buttons.h"

void setup()
{	
	Serial.begin(9600);
	fan_setup();
	BME280_setup();
	damper_setup();
	lcd_setup();
}

void loop()
{
	if (state_button1() == 0)
	{
		if (damper_state() == 0)
			open_damper();
		else
			close_damper();
		delay(1000);
	}
	if (state_button2() == 0)
	{
		if (fan_state() == 0)
			fan_on();
		else
			fan_off();
		delay(1000);
	}
	display_values();
	delay(100);
}

