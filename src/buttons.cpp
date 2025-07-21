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

bool last_state_b1 = false;
bool last_state_b2 = false;
bool last_state_b3 = false;

void buttons_setup()
{
    pinMode(pin_button1, INPUT_PULLUP);
	pinMode(pin_button2, INPUT_PULLUP);
	pinMode(pin_button3, INPUT_PULLUP);
}

bool button1_pressed()
{
	if (digitalRead(pin_button1) == LOW && last_state_b1 == false)
	{
		delay(100);
		last_state_b1 = true;
		return (true);
	}
	else if (digitalRead(pin_button1) == HIGH)
	{
		last_state_b1 = false;
	}
	return (false);
}


bool button2_pressed()
{
	if (digitalRead(pin_button2) == LOW && last_state_b2 == false)
	{
		delay(100);
		last_state_b2 = true;
		return (true);
	}
	else if (digitalRead(pin_button2) == HIGH)
	{
		last_state_b2 = false;
	}
	return (false);
}

bool button3_pressed()
{
	if (digitalRead(pin_button3) == LOW && last_state_b3 == false)
	{
		delay(100);
		last_state_b3 = true;
		return (true);
	}
	else if (digitalRead(pin_button3) == HIGH)
	{
		last_state_b3 = false;
	}
	return (false);
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
