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
#include "graph.h"
#include "data.h"

char text_state[12];
int time_LCD;
unsigned long	timestamp_display = 0;
const int		time_display = 5; // Sekunden
int				modus_display = 0;

void display()
{
	if (modus_display == 0)
		show_logo();
	if (modus_display == 1)
		show_values();
	if (modus_display == 2)
		plot_graph(get_ring_buffer(1), "rF", 20, 80);
	if (modus_display == 3)
		plot_graph(get_ring_buffer(0), "T", 15, 60);
	if (modus_display == 4)
		plot_graph(get_ring_buffer(2), "aF", 0, 30); 
	if (timestamp_now_s() - timestamp_display > time_display)
	{
		modus_display++;
		if (modus_display > 4)
			modus_display = 1;
		timestamp_display = timestamp_now_s();
	}
}

void show_values()
{
	clear_lcd();
	set_position_cursor_lcd(0,0);
	print_state();
	print_time();
	print_values_BME280();
	print_values_DS18B20();
	print_max_temp();
	print_state_damper();
	print_state_fan();
	//print_values_buttons();
	display_on_lcd();
}

void clear_text_state()
{
	text_state[0] = 0;
}

void set_text_state(char *text)
{
	int i;

	i = 0;	
	while  (i < 11 && text[i]  != 0)
	{
		text_state[i] = text[i];
		i++;
	}
	text_state[i] = 0;
}

void set_time_LCD(unsigned long nb)
{
	time_LCD = (int)nb;
}

void print_time()
{
	print_str_lcd("Dauer:      ");
	print_int_lcd(time_LCD);
	print_str_lcd(" s\n");
}

void print_state()
{
	print_str_lcd("Status:     ");
	print_str_lcd(text_state);
	print_str_lcd("\n");
}