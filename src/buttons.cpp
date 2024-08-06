/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:53:18 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/06 22:53:18 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include "buttons.h"
#include "lcd.h"

int pin_button1 = 3;
int pin_button2 = 4;
int pin_button3 = 5;

void buttons_setup()
{
    pinMode(pin_button1, INPUT_PULLUP);
	pinMode(pin_button2, INPUT_PULLUP);
	pinMode(pin_button3, INPUT_PULLUP);
}

int state_button1()
{
	return(digitalRead(pin_button1));
}

int state_button2()
{
	return(digitalRead(pin_button2));
}

int state_button3()
{
	return(digitalRead(pin_button3));
}

void print_values_buttons()
{
	print_str_lcd("Taster 1:   ");
  	print_float_lcd(state_button1());
	print_str_lcd("\n");
	print_str_lcd("Taster 2:   ");
  	print_float_lcd(state_button2());
	print_str_lcd("\n");
	print_str_lcd("Taster 3:   ");
  	print_float_lcd(state_button3());
	print_str_lcd("\n");
}
