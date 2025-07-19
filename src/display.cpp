#include "Arduino.h"
#include "display.h"
#include "lcd.h"
#include "damper.h"
#include "fan.h"
#include "bme280.h"
#include "ds18B20.h"
#include "buttons.h"
#include "storage.h"
#include "damper_logic.h"

char text_status[12];
int time;

void display_values()
{
	clear_lcd();
	set_position_cursor_lcd(0,0);
	print_state_damper();
	print_state_fan();
	print_values_BME280();
	print_values_DS18B20();
	print_values_buttons();
	print_storage();
	print_status();
	print_time();
	display_on_lcd();
}

void clear_text_state()
{
	text_status[0] = 0;
}

void set_text_state(char *text)
{
	int i;

	i = 0;	
	while  (i < 11 && text[i]  != 0)
	{
		text_status[i] = text[i];
		i++;
	}
	text_status[i] = 0;
}

void set_time_LCD(unsigned long nb)
{
	time = (int)nb;
}

void print_time()
{
	print_str_lcd("Dauer: ");
	print_int_lcd(time);
	print_str_lcd(" s\n");
}

void print_status()
{
	print_str_lcd("Status: ");
	print_str_lcd(text_status);
	print_str_lcd("\n");
}