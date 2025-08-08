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

#ifndef DISPLAY_H
#define DISPLAY_H

enum ModusDisplay {
    Display_Values,
	Display_Menue,
    NUM_ModusDisplay  // entspricht x + 1, wichtig für Schleifen etc.
};

void display();
void set_modus_display(int nb);
int get_modus_display();
void clear_text_state();
void set_text_state(char *text);
void print_state();
void print_time();
void set_time_LCD(unsigned long nb);
void show_values_1();
void show_values_2();
void display_values();
void print_abs_humidity();
void print_zyklus();
void print_info();

#endif