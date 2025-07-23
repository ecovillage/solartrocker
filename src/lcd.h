/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:03:37 by jweingar          #+#    #+#             */
/*   Updated: 2024/07/03 15:03:37 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCD_H
#define LCD_H

void lcd_setup();
void clear_lcd();
void  setTextColor_display(uint16_t c, uint16_t bg);
void print_str_lcd(const char *str);
void print_char_lcd(char c);
void print_float_lcd(float nbr);
void print_int_lcd(int nbr);
void set_position_cursor_lcd(int row, int column);
void display_on_lcd();
void show_logo();
void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void drawPixel(int16_t x, int16_t y, uint16_t color);
int get_screen_height();
int get_screen_width();

#endif