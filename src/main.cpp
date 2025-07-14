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
#include "webserver.h"
#include <Wire.h>



void receiveEvent(int);
void requestEvent();
static int i2c_target = 4;

void setup()
{
	
	Serial.begin(9600);
	fan_setup();
	BME280_setup();
	damper_setup();
	lcd_setup();
	buttons_setup();
	//webserver_setup();
	Wire.begin();
}

void loop()
{
	if (!button1_pressed() && !button2_pressed() && !button3_pressed()){
		if (!check_humidity())
			check_fan_neccessary();
	}
	if (button1_pressed())
	{
		open_damper();
		delay(200);
		//return ;
	}
	if (button2_pressed())
	{
		if (fan_state() == 0)
			fan_on();
		else
			fan_off();
		delay(200);
		//return ;
	}
	if (button3_pressed())
	{
		//set_modus(read_modus() + 1);
		reset_max_temp();
		delay(200);
	}
	save_max_temp();
	display_values();
	collect_data();
	delay(5000);
}

