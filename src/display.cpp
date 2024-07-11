#include "Arduino.h"
#include "display.h"
#include "lcd.h"
#include "damper.h"
#include "fan.h"
#include "bme280.h"


void display_values()
{
	clear_lcd();
	set_position_cursor_lcd(0,0);
	print_state_damper();
	print_state_fan();
	print_values_BME280();
	display_on_lcd();
}