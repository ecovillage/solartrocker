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

const int max_values = 100;
float ring_buffer[max_values][3];
int act_nb;
unsigned long  timestamp_last_save;
const int interval = 5 * 60 * 1000; // = 5 Min
boolean	first_round = 1;


void data_setup()
{
    timestamp_last_save = millis();
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

void collect_data()
{
    if (millis() - timestamp_last_save > interval)
	{
		if (act_nb == max_values)
		{
			act_nb = 0;
			first_round = 0;
		}
		ring_buffer[act_nb][0] = read_bme_temperature();
		ring_buffer[act_nb][1] = read_bme_humidity();
		ring_buffer[act_nb][2] = read_temp(0);
		act_nb++;
		timestamp_last_save = millis();
	}
}
