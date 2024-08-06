/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luefter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:03:37 by jweingar          #+#    #+#             */
/*   Updated: 2024/07/03 15:03:37 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include "fan.h"
#include "lcd.h"

int FanPin = 6; // Beispiel für Pin 13, ändere dies entsprechend deinem Setup
int state_fan;

void fan_setup()
{
    pinMode(FanPin, OUTPUT); // Den Pin als Ausgang konfigurieren
	fan_off();
}

void fan_on()
{
    digitalWrite(FanPin, HIGH);
	state_fan = 1;
}

void fan_off()
{
	digitalWrite(FanPin, LOW);
	state_fan = 0;
}

int fan_state()
{
	return (state_fan);
}

void print_state_fan()
{
    //clear_lcd();
	//set_position_cursor_lcd(0,0);
    print_str_lcd("Ventilator: ");
	if (fan_state())
		print_str_lcd("an");
	else
		print_str_lcd("aus");
	print_str_lcd("\n");	
}