#include <Arduino.h>
#include "fan.h"
#include "damper.h"
#include "lcd.h"
#include "bme280.h"
#include "display.h"

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
	fan_on();
	open_damper();
	display_values();
	delay(1000);
	fan_off();
	close_damper();
	display_values();
	delay(1000);
}

