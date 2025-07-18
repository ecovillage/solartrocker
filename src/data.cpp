/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:53:31 by marvin            #+#    #+#             */
/*   Updated: 2024/08/16 16:53:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include "bme280.h"
#include "ds18B20.h"
#include "damper_logic.h"
#include "damper.h"
#include "fan.h"
#include "data.h"

const int max_values = 30;
float ring_buffer[max_values][3];
int act_nb;
unsigned long  timestamp_last_save;
const int interval = 2 * 60; // in Sekunden
boolean	first_round = 1;


void data_setup()
{
    timestamp_last_save = timestamp_now_s();
	act_nb = 0;
}

float avarage_temp_bme()
{
	float	sum;
	int		i;
	int		max;

	sum = 0;
	i = 0;
	max = act_nb;
	while (i <= max)
	{
		if (!first_round)
			max = max_values - 1;
		sum += ring_buffer[i][0];
		i++;
	}
	return (sum/(max + 1));
}

float avarage_humidity_bme()
{
	float	sum;
	int		i;
	int		max;

	sum = 0;
	i = 0;
	max = act_nb;
	while (i <= max)
	{
		if (!first_round)
			max = max_values - 1;
		sum += ring_buffer[i][1];
		i++;
	}
	return (sum/(max + 1));
}

float delta_min_max_humidity_bme() //gibt die Differenz zwischen max H und min H aus dem Ringbuffer zurück, außer bei ersten Füllen des Ringbuffers
{
	float	min_h;
	float	max_h;
	int		i;
	int		max;

	i = 0;
	min_h = 100;
	max_h = 0;
	max = act_nb;
	if (first_round)
		return (100);
	while (i <= max_values - 1)
	{
		if (ring_buffer[i][1] > max_h)
			max_h = ring_buffer[i][1];
		else if (ring_buffer[i][1] < min_h)
			min_h = ring_buffer[i][1];
		i++;
	}
	return (max_h - min_h);
}

void collect_data()
{
	if (timestamp_now_s() - timestamp_last_save > interval)
	{
		if (act_nb == max_values)
		{
			act_nb = 0;
			first_round = 0;
		}
		ring_buffer[act_nb][0] = read_bme_temperature();
		ring_buffer[act_nb][1] = read_bme_humidity();
		ring_buffer[act_nb][2] = read_temp(0);
		send_data_UART();
		act_nb++;
		timestamp_last_save = timestamp_now_s();
	}
}

void send_data_UART()
{
	Serial.print("timestamp;");
	Serial.print(timestamp_last_save);
	Serial.print(";t_bme;");
	Serial.print(read_bme_temperature(),2);
	Serial.print(";h_bme;");
	Serial.print(read_bme_humidity(),2);
	Serial.print(";t_0;");
	Serial.print(read_temp(0),2);
	Serial.print(";state_damper;");
	Serial.print(get_damper_state());
	Serial.print(";state_fan;");
	Serial.print(get_fan_state());
	Serial.print(";state;");
	Serial.print(get_state());
	Serial.println(";");
}