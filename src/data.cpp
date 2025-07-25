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

const int max_values = 100;
float ring_buffer[4][max_values];
unsigned long  timestamp_last_save;
const int interval = 20; // in Sekunden
bool	first_round = 1;


void data_setup()
{
    timestamp_last_save = timestamp_now_s();
	ring_buffer[0][max_values - 1] = -1;
}

float avarage_ringbuffer(int value)
{
	float	sum;

	sum = 0;
	for (int i = 0; i <= max_values - 1; i++)
		sum += ring_buffer[value][i];
	return (sum/(max_values));
}

float delta_min_max_abs_humidity() //gibt die Differenz zwischen max H und min H aus dem Ringbuffer zurück, außer bei ersten Füllen des Ringbuffers
{
	float	min_h;
	float	max_h;
	int		i;
	int		max;

	i = 0;
	min_h = 100;
	max_h = 0;
	if (first_round)
		return (100);
	while (i <= max_values - 1)
	{
		if (ring_buffer[3][i] > max_h)
			max_h = ring_buffer[1][i];
		else if (ring_buffer[3][i] < min_h)
			min_h = ring_buffer[3][i];
		i++;
	}
	return (max_h - min_h);
}

void collect_data()
{
	if (timestamp_now_s() - timestamp_last_save > interval)
	{
		if (ring_buffer[0][0] != -1)
			first_round = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < max_values - 1; j++)
				ring_buffer[i][j] = ring_buffer[i][j + 1];
		}
		ring_buffer[0][max_values - 1] = read_bme_temperature();
		ring_buffer[1][max_values - 1] = read_bme_humidity();
		ring_buffer[2][max_values - 1] = read_temp(0);
		ring_buffer[3][max_values - 1] = calculateAbsoluteHumidity(ring_buffer[0][max_values - 1], ring_buffer[1][max_values - 1]);
		send_data_UART();
		timestamp_last_save = timestamp_now_s();
	}
}

void send_data_UART()
{
	Serial.print("timestamp;");
	Serial.print(timestamp_last_save);
	Serial.print(";t_bme;");
	Serial.print(ring_buffer[0][max_values - 1],2);
	Serial.print(";h_bme;");
	Serial.print(ring_buffer[1][max_values - 1],2);
	Serial.print(";t_0;");
	Serial.print(ring_buffer[2][max_values - 1],2);
	Serial.print(";AbsoluteHumidity;");
	Serial.print(ring_buffer[3][max_values - 1],2);	
	Serial.print(";state_damper;");
	Serial.print(get_damper_state());
	Serial.print(";state_fan;");
	Serial.print(get_fan_state());
	Serial.print(";state;");
	Serial.print(get_state());
	Serial.println(";");
}

float calculateAbsoluteHumidity(float temperature, float relativeHumidity) //ChatGPT
{
	float saturationVaporPressure;
	float absoluteHumidity;

    saturationVaporPressure = 6.112f * expf((17.67f * temperature) / (temperature + 243.5f)); // Sättigungsdampfdruck (Magnus-Formel)
    absoluteHumidity = (saturationVaporPressure * (relativeHumidity / 100.0f) * 2.1674f) / (273.15f + temperature);  // Absolute Feuchte (in g/m³)
    
    return (absoluteHumidity);
}

float calculatePineEMC(float temperature, float relativeHumidity) //ChatGPT
{
	float h = relativeHumidity / 100.0f;  // rF in Dezimalform (0..1)
	float T_Kelvin = temperature + 273.15f;

    // Kiefer-spezifische Koeffizienten
    float K = 0.81f * exp(4800.0f / (8.314f * T_Kelvin));  // Q = 4800 J/mol
    float K1 = 4.7f;
    float K2 = 0.53f;

    // Berechnung
    float term1 = (K * h) / (1.0f + K * h);
    float term2 = (K1 * K * h + 2.0f * K1 * K2 * K * K * h * h);
    float term3 = (1.0f + K1 * K * h + K1 * K2 * K * K * h * h);
    float EMC = (1800.0f / 18.0f) * (term1 + (term2 / term3));

    return EMC;
}

float* get_ring_buffer(int i)
{
	return (ring_buffer[i]);
}

int get_max_values()
{
	return (max_values);
}