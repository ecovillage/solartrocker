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
#include "sht3x.h"
#include <Adafruit_SSD1306.h>

char text_state[12];
unsigned long time_LCD;
unsigned long	timestamp_display = 0;
const int		time_display = 5; // Sekunden
int				modus_display = 0;

void display()
{
	if (modus_display == 0)
		show_logo();
	if (modus_display == 1)
		show_values_1();
	if (modus_display == 2)
		show_values_2();
	if (modus_display == 3)
		plot_graph(get_ring_buffer(T_innen), "T (°C)");
	if (modus_display == 4)
		plot_graph(get_ring_buffer(F_innen), "rF (%)");
	if (modus_display == 5)
		plot_graph(get_ring_buffer(F_abs_innen), "aF (g/m3)"); 
	if (timestamp_now_s() - timestamp_display > time_display)
	{
		modus_display++;
		if (modus_display > 5)
			modus_display = 1;
		timestamp_display = timestamp_now_s();
	}
}

void show_values_1()
{
	clear_lcd();
	set_position_cursor_lcd(0,0);
	setTextColor_display(WHITE, BLACK);
	print_state();
	print_time();
	print_max_temp();
	print_state_damper();
	print_state_fan();
	display_on_lcd();
}

void show_values_2()
{
	clear_lcd();
	set_position_cursor_lcd(0,0);
	setTextColor_display(WHITE, BLACK);

	print_str_lcd("T(innen):   "); 
    print_float_lcd(read_innen_temperature());
    print_str_lcd(" °C\n");
	
	print_str_lcd("T(aussen):  "); 
    print_float_lcd(read_aussen_temperature());
    print_str_lcd(" °C\n");
	
	print_str_lcd("T(Holz):    "); 
    print_float_lcd(read_holz_temperature());
    print_str_lcd(" °C\n");
	
	print_str_lcd("F(innen):   "); 
    print_float_lcd(read_innen_humidity());
    print_str_lcd(" %RH\n");
	
	print_str_lcd("F(aussen):  "); 
    print_float_lcd(read_aussen_humidity());
    print_str_lcd(" %RH\n");
	
	print_str_lcd("F(Holz):    "); 
    print_float_lcd(read_holz_humidity());
    print_str_lcd(" %RH\n");
	
	print_str_lcd("F(abs):     "); 
    print_float_lcd(calculateAbsoluteHumidity(read_innen_temperature(), read_innen_humidity()));
    print_str_lcd(" g/m3\n");

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
	time_LCD = nb;
}

void print_time()
{
    int hours = time_LCD / 3600;
    int minutes = (time_LCD % 3600) / 60;
    int seconds = time_LCD % 60;

    print_str_lcd("Dauer:      ");
    if (hours < 10)
		print_char_lcd('0');
    print_int_lcd(hours);
    print_char_lcd(':');
    if (minutes < 10)
		print_char_lcd('0');
    print_int_lcd(minutes);
    print_char_lcd(':');
    if (seconds < 10)
		print_char_lcd('0');
    print_int_lcd(seconds);

    print_str_lcd("\n");
}

void print_state()
{
	print_str_lcd("Status:     ");
	print_str_lcd(text_state);
	print_str_lcd("\n");
}

void print_abs_humidity()
{
	print_str_lcd("F(abs):     "); 
    print_float_lcd(calculateAbsoluteHumidity(read_innen_temperature(), read_innen_humidity()));
    print_str_lcd(" g/m3\n");
}