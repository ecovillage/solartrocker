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
#include "menue.h"

void setup()
{
	Serial1.begin(9600);
	Serial.begin(9600);
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
	collect_data();
}

void loop()
{
	if (get_modus_display() != Display_Menue)
		if (button1_pressed())
		{
			set_selectedItem(0);
			set_modus_display(Display_Menue);
		}
	if (get_state() == Auto)
		state_auto();
	else if (get_state() == Lueften)
		state_dehydrating();
	else if (get_state() == Heizen)
		state_heating();
	else if (get_state() == RF_const)
		state_RF_const();
	else if (get_state() == Manuel)
		state_manuel();
	else if (get_state() == Night)
		state_night();
	save_max_temp();
	display();
	collect_data();
	delay(100);

}
