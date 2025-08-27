/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dampers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:08:47 by jweingar          #+#    #+#             */
/*   Updated: 2024/07/03 15:08:47 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include "damper.h"
#include "lcd.h"
#include "damper_logic.h"

int pin_Motor = 7; // Beispiel für Pin 13, ändere dies entsprechend deinem Setup
int state_damper;

void damper_setup()
{
    pinMode(pin_Motor, OUTPUT);
	close_damper();
}

void open_damper()
{
	if (state_damper == 0)
	{
		digitalWrite(pin_Motor, HIGH);
		state_damper = 1;
		add_to_summe_wasser();
	}
}


void close_damper()
{
	if (state_damper == 1)
	{
		digitalWrite(pin_Motor, LOW);
		state_damper = 0;
		set_f_a_innen_close_damper();
	}
}

int get_damper_state()
{
	return (state_damper);
}

void print_state_damper()
{
    //clear_lcd();
	//set_position_cursor_lcd(0,0);
    print_str_lcd("Klappen:    ");
	if (get_damper_state())
		print_str_lcd("auf");
	else
		print_str_lcd("zu");
	print_str_lcd("\n");	
}