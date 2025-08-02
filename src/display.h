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

void clear_text_state();
void set_text_state(char *text);
void print_state();
void print_time();
void set_time_LCD(unsigned long nb);
void show_values_1();
void show_values_2();
void display();
void print_abs_humidity();
void print_zyklus();

#endif