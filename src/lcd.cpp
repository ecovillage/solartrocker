/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:21:37 by jweingar          #+#    #+#             */
/*   Updated: 2024/07/03 11:21:37 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include <Adafruit_SSD1306.h>
#include "lcd.h"
#include "buttons.h"
#include "fan.h"
#include "siebenlindenlogo.h"

// Display
#define OLED_MOSI    9
#define OLED_CLK    10
#define OLED_DC     11
#define OLED_CS     12
#define OLED_RESET  13
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void lcd_setup()
{
	display.begin(SSD1306_SWITCHCAPVCC);
	display.clearDisplay();
	display.setTextSize(1);
    display.setTextColor(WHITE);
}

void clear_lcd()
{
	display.clearDisplay();
}

void set_position_cursor_lcd(int row, int column)
{
	display.setCursor(row, column);
}

void  setTextColor_display(uint16_t c, uint16_t bg)
{
	display.setTextColor(c, bg);
}

void print_str_lcd(const char *str)
{
	display.print(str);
}

void print_char_lcd(char c)
{
	display.print(c);
}

void print_float_lcd(float nbr)
{
	display.print(nbr, 1);
}

void print_int_lcd(int nbr)
{
	display.print(nbr);
}

void display_on_lcd()
{
	display.display();
}

void show_logo() {
  display.clearDisplay();
  display.drawBitmap(0, 0, siebenLindenLogo, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}

void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	display.drawFastHLine(x, y, w , color);
}

void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	display.drawFastVLine(x, y, h , color);
}

void drawPixel(int16_t x, int16_t y, uint16_t color)
{
	display.drawPixel(x, y, color);
}

int get_screen_height()
{
	return(SCREEN_HEIGHT);
}

int get_screen_width()
{
	return(SCREEN_WIDTH);
}