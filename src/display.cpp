#include "Arduino.h"
#include "display.h"
#include "lcd.h"
#include "damper.h"
#include "fan.h"
#include "bme280.h"
#include "ds18B20.h"
#include "buttons.h"


void display_values()
{
	clear_lcd();
	set_position_cursor_lcd(0,0);
	print_state_damper();
	print_state_fan();
	print_values_BME280();
	print_values_DS18B20();
	print_values_buttons();
	display_on_lcd();
}