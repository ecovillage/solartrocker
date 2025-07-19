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



//void receiveEvent(int);
//void requestEvent();
//static int i2c_target = 4;
unsigned long	timestamp_state_manuel = 0;
const int		time_state_manuel = 0.5 * 60; // Sekunden

void state_manuel()
{
	if (button1_pressed())
	{
		open_damper();
		delay(200);
	}
	else
		close_damper();
	if (button2_pressed())
	{
		if (get_fan_state() == 0)
			fan_on();
		else
			fan_off();
		delay(200);
	}
	if (button3_pressed())
	{
		//set_modus(read_modus() + 1);
		reset_max_temp();
		delay(200);
	}
	if (timestamp_now_s() - timestamp_state_manuel > time_state_manuel)
		set_state(0);
}

void setup()
{
	Serial.begin(9600);
	Serial.println("Starte Solartrockner!");
	fan_setup();
	BME280_setup();
	damper_setup();
	lcd_setup();
	buttons_setup();
	//webserver_setup();
	Wire.begin();
	set_state(0);
}

void loop()
{
	if (button1_pressed() || button2_pressed() || button3_pressed()){
		set_state(4);
		timestamp_state_manuel = timestamp_now_s();
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
