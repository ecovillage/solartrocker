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

boolean button1_pressed()
{
	return (digitalRead(pin_button1) == LOW);
}

boolean button2_pressed()
{
	return (digitalRead(pin_button2) == LOW);
}

boolean button3_pressed()
{
	return (digitalRead(pin_button3) == LOW);
}

void print_values_buttons()
{
	print_str_lcd("Taster1,2,3:");
  	print_int_lcd(button1_pressed());
	print_str_lcd(",");
  	print_int_lcd(button2_pressed());
	print_str_lcd(",");
  	print_int_lcd(button3_pressed());
	print_str_lcd("\n");
}
