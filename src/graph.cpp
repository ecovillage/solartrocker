/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:50:48 by jweingar          #+#    #+#             */
/*   Updated: 2025/07/23 12:50:48 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include "graph.h"
#include "lcd.h"
#include <Adafruit_SSD1306.h>
#include "data.h"

void draw_graph(float *graph, float b_min, float b_max)
{
	int	a;
	int	b;

	if (b_max <= b_min)
    	return ;

	for (int i = 0; i < get_max_values() - 1; i++)
	{
		a = get_screen_height() - 1 - (int)((graph[i] - b_min) / (b_max - b_min) * 60.0f);
		b = get_screen_height() - 1 - (int)((graph[i + 1] - b_min) / (b_max - b_min) * 60.0f);
		
		drawFastVLine(13 + i, min(a, b), max(1, abs(a - b)), WHITE);
		//drawPixel(13 + i, get_screen_height() - 1 - (int)((graph[i] - b_min) / (b_max - b_min) * 60.0f), WHITE);
	}
}

void draw_background(char *text, int b_min, int b_max)
{
	drawFastHLine(strlen(text) * 6, get_screen_height() - 1 - 60, get_screen_width(), WHITE);
	drawFastHLine(0, get_screen_height() - 1 - 40, get_screen_width(), WHITE);
	drawFastHLine(0, get_screen_height() - 1 - 20, get_screen_width(), WHITE);
	drawFastHLine(0, get_screen_height() - 1 - 0, get_screen_width(), WHITE);
	set_position_cursor_lcd(0, 0);
	print_str_lcd(text);
	set_position_cursor_lcd(0, 15);
	print_int_lcd(b_min + (b_max - b_min) / 3 * 2);
	set_position_cursor_lcd(0, 35);
	print_int_lcd(b_min + (b_max - b_min) / 3);
	set_position_cursor_lcd(0, 55);
	print_int_lcd((int)b_min);
}

void plot_graph(float *graph, char *text)
{
	float b_min;
	float b_max;
	float range;
	float step;

	b_min = floorf(min_array(graph, get_max_values()));
	range = ceilf(max_array(graph, get_max_values())) - b_min;
	step = 3.0f;
	b_max = ceilf(range / step) * step + b_min;

	clear_lcd();
	setTextColor_display(WHITE, BLACK);
	draw_background(text, b_min, b_max);
	draw_graph(graph, b_min, b_max);
	display_on_lcd();
}