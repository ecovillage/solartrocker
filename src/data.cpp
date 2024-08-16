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

int max_values = 100;
int fifo_Bufffer[max_values];
unsigned long  timestamp_last_save;
int interval = 60 * 5 * 1000;

void data_init()
{
    timestamp_last_save = millis();
}

void save_data()
{
    if (timestamp_last_save - millis() < )
}