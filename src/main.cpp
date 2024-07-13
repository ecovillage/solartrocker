#include <Arduino.h>
#include "fan.h"
#include "damper.h"
#include "lcd.h"
#include "bme280.h"
#include "display.h"
#include "ds18B20.h"

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
	if (read_temp(0) > 30)
		open_damper();
	else
		close_damper();
	display_values();
	delay(1000);
}

