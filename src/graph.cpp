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

void draw_graph(float *graph, int b_min, int b_max)
{
  //display.clearDisplay();
  for (int i = 0; i < get_max_values() - 1; i++)
  {
     drawPixel(13 + i, get_screen_height() - 1 - ((graph[i] - b_min) / (b_max - b_min) * 60), WHITE);
  }
  //display.display();
}

void draw_background(char *text, int b_min, int b_max)
{
  drawFastHLine(13, get_screen_height() - 1 - 60, get_screen_width(), WHITE);
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
  print_int_lcd(b_min);
}

void plot_graph(float *graph, char *text, int b_min, int b_max)
{
  clear_lcd();
  draw_background(text, b_min, b_max);
  draw_graph(graph, b_min, b_max);
  display_on_lcd();
}