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
#include "storage.h"
#include "sht3x.h"

const int max_values = 110;
float ring_buffer[NUM_VALUES][max_values];
unsigned long  timestamp_last_save;
const int interval = 20; // in Sekunden
bool	first_round = true;




void data_setup()
{
    timestamp_last_save = timestamp_now_s();
	//set_zyklus(134);
	increase_zyklus();
	//send_headline_UART();
}

bool is_first_round()
{
	return (first_round);
}

float avarage_ringbuffer(int value)
{
	float	sum;

	sum = 0;
	for (int i = 0; i <= max_values - 1; i++)
		sum += ring_buffer[value][i];
	return (sum/(max_values));
}

float min_array(float *arr, const int size) //gibt die Differenz zwischen max H und min H aus dem Ringbuffer zurück, außer bei ersten Füllen des Ringbuffers
{
	float	arr_min;
	if (!arr)
		return (0);
	arr_min = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] < arr_min)
			arr_min = arr[i];
	}
	return (arr_min);
}

float max_array(float *arr, const int size) //gibt die Differenz zwischen max H und min H aus dem Ringbuffer zurück, außer bei ersten Füllen des Ringbuffers
{
	float	arr_max;
	if (!arr)
		return (0);
	arr_max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > arr_max)
			arr_max = arr[i];
	}
	return (arr_max);
}

float delta_min_max_abs_humidity() //gibt die Differenz zwischen max H und min H aus dem Ringbuffer zurück, außer bei ersten Füllen des Ringbuffers
{
	float	min_h;
	float	max_h;

	min_h = ring_buffer[F_abs_innen][0];
	max_h = ring_buffer[F_abs_innen][0];
	for (int i = 0; i <= max_values - 1; i++)
	{
		if (ring_buffer[F_abs_innen][i] > max_h)
			max_h = ring_buffer[F_abs_innen][i];
		else if (ring_buffer[F_abs_innen][i] < min_h)
			min_h = ring_buffer[F_abs_innen][i];
	}
	return (max_h - min_h);
}

void collect_data()
{
	if (timestamp_now_s() - timestamp_last_save > interval)
	{
		if (ring_buffer[0][0] != 0)
			first_round = false;
		for (int i = 0; i < NUM_VALUES; i++)
		{
			for (int j = 0; j < max_values - 1; j++)
				ring_buffer[i][j] = ring_buffer[i][j + 1];
		}
		ring_buffer[T_innen][max_values - 1] = read_innen_temperature();
		ring_buffer[F_innen][max_values - 1] = read_innen_humidity();
		ring_buffer[F_abs_innen][max_values - 1] = calculateAbsoluteHumidity(ring_buffer[T_innen][max_values - 1], ring_buffer[F_innen][max_values - 1]);
		send_data_UART();
		timestamp_last_save = timestamp_now_s();
	}
}

void send_headline_UART()
{
	Serial1.print(F("zyklus;"));
	Serial1.print(F("timestamp;"));
	Serial1.print(F("T_innen;"));
	Serial1.print(F("F_innen;"));
	Serial1.print(F("T_aussen;"));
	Serial1.print(F("F_aussen;"));
	Serial1.print(F("T_Holz;"));
	Serial1.print(F("F_Holz;"));
	Serial1.print(F("F_abs_innen;"));
	Serial1.print(F("state_damper;"));
	Serial1.print(F("state_fan;"));
	Serial1.print(F("state;"));
}

void send_data_UART()
{

	Serial1.print(get_zyklus());
	Serial1.print(';');
	Serial1.print(timestamp_last_save);
	Serial1.print(';');
	printFloat_1digit(read_innen_temperature());
	Serial1.print(';');
	printFloat_1digit(read_innen_humidity());
	Serial1.print(';');
	printFloat_1digit(read_aussen_temperature());
	Serial1.print(';');
	Serial1.flush();
	printFloat_1digit(read_aussen_humidity());
	Serial1.print(';');
	printFloat_1digit(read_holz_temperature());
	Serial1.print(';');
	printFloat_1digit(read_holz_humidity());
	Serial1.print(';');
	printFloat_1digit(calculateAbsoluteHumidity(read_innen_temperature(), read_innen_humidity()));
	Serial1.print(';');
	Serial1.print(get_damper_state());
	Serial1.print(';');
	Serial1.print(get_fan_state());
	Serial1.print(';');
	Serial1.print(get_state());
	Serial1.println(';');
	Serial1.flush();
}

// Berechnet die neue relative Feuchte nach Temperaturänderung
float humidity_changed_temperature(float t_begin, float h_begin, float t_end) {
	// Dampfdruck bleibt gleich (konstante absolute Feuchte)
    float e_s_begin = saturation_vapor_pressure(t_begin);
    float e = h_begin / 100.0f * e_s_begin;
	
    float e_s_end = saturation_vapor_pressure(t_end);
    float h_end = (e / e_s_end) * 100.0f;
	
    return h_end;
}

float saturation_vapor_pressure(float temperature)
{
	return (6.112f * expf((17.67f * temperature) / (temperature + 243.5f)));
}

float calculateAbsoluteHumidity(float temperature, float relativeHumidity) //ChatGPT
{
	float absoluteHumidity;

    absoluteHumidity = (saturation_vapor_pressure(temperature) * 100.0f * (relativeHumidity / 100.0f) * 2.1674f) / (273.15f + temperature);  // Absolute Feuchte (in g/m³)
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

    return (EMC);
}

float* get_ring_buffer(int i)
{
	return (ring_buffer[i]);
}

int get_max_values()
{
	return (max_values);
}

void printFloat_1digit(float f) { //ChatGPT
  int ganz = (int)f;
  int nachkomma = abs((int)(f * 10) % 10);
  Serial1.print(ganz);
  Serial1.print('.');
  Serial1.print(nachkomma);
}

//Memorykapazität anzeigen von ChatGPT
extern int __heap_start;
extern void *__brkval;

int freeMemory()
{
	int v;
	int freeMem;

	if (__brkval == 0)
		freeMem = (int)&v - (int)&__heap_start;
	else
		freeMem = (int)&v - (int)__brkval;
	return (freeMem);
}