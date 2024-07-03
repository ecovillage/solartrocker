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

#include <Arduino.h>

int pin_Motor = 14;
int pin_Direction = 15;
int pin_LimitSwitchOpen = 16; // HIGH = NOT pushed, LOW = pushed
int pin_LimitSwitchClose = 18;
int state_dampers;

void damper_setup()
{
    pinMode(pin_Motor, OUTPUT);
	pinMode(pin_Direction, OUTPUT);
	pinMode(pin_LimitSwitchOpen, INPUT);
	pinMode(pin_LimitSwitchClose, INPUT);
	close_damper();
}

void damper_motor_on()
{
	digitalWrite(pin_Motor, HIGH);
}

void damper_motor_off()
{
	digitalWrite(pin_Motor, LOW);
}

void motordirection_right()
{
	digitalWrite(pin_Direction, HIGH);
}

void motordirection_left()
{
	digitalWrite(pin_Direction, LOW);
}

void open_damper()
{
    if (digitalRead(pin_LimitSwitchOpen))
	{
		motordirection_right();
		damper_motor_on();
		while (!digitalRead(pin_LimitSwitchOpen))
		{
			sleep(0.1);
		}
		damper_motor_off();
		state_dampers = 1;
	}
}

void close_damper()
{
	if (digitalRead(pin_LimitSwitchClose))
	{
		motordirection_left();
		damper_motor_on();
		while (!digitalRead(pin_LimitSwitchClose))
		{
			sleep(0.1);
		}
		damper_motor_off();
		state_dampers = 0;
	}
}

int return_state_dampers()
{
	return (state_dampers);
}