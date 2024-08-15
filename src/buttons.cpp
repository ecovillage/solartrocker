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

int pin_button1 = 5;
int pin_button2 = 4;
int pin_button3 = 3;

void buttons_setup()
{
    pinMode(pin_button1, INPUT_PULLUP);
	pinMode(pin_button2, INPUT_PULLUP);
	pinMode(pin_button3, INPUT_PULLUP);
}

int state_button1()
{
	if (digitalRead(pin_button1) == LOW)
		return (1);
	else
		return (0);
}

int state_button2()
{
	if (digitalRead(pin_button2) == LOW)
		return (1);
	else
		return (0);
}

int state_button3()
{
	if (digitalRead(pin_button3) == LOW)
		return (1);
	else
		return (0);
}

void print_values_buttons()
{
	print_str_lcd("Taster1,2,3:");
  	print_int_lcd(state_button1());
	print_str_lcd(",");
  	print_int_lcd(state_button2());
	print_str_lcd(",");
  	print_int_lcd(state_button3());
	print_str_lcd("\n");
}
