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

int FanPin = 13; // Beispiel für Pin 13, ändere dies entsprechend deinem Setup
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