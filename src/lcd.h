/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fan.h                                              :+:      :+:    :+:   */
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
void print_str_lcd(char *str);
void print_char_lcd(char c);
void print_float_lcd(float nbr);
void set_position_cursor_lcd(int row, int column);
void display_on_lcd();

#endif