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

int pin_create_file = 14;
int pin_LDR = 15;

const int max_values = 110;
char infotext[50] = "";
float ring_buffer[NUM_ValueIndex][max_values] = {0};
unsigned long  timestamp_last_save;
const int interval = 20; // in Sekunden, Standart = 20
bool	first_round = true;


void data_setup()
{
    timestamp_last_save = timestamp_now_s();
	//set_zyklus(134);
	increase_zyklus();
	pinMode(pin_create_file, OUTPUT);
 	digitalWrite(pin_create_file, HIGH);
	create_new_file();
	init_ring_buffer();
	infotext[sizeof(infotext)-1] = '\0';
}

void init_ring_buffer()
{
    for (int i = 0; i < max_values; i++)
        ring_buffer[Helligkeit][i] = 1000.0f;
}

bool is_first_round()
{
	return (first_round);
}

float avarage_ringbuffer(int value, int nb)
{
	float	sum;

	sum = 0;
	for (int i = max_values - nb; i <= max_values - 1; i++)
		sum += ring_buffer[value][i];
	return (sum/nb);
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
		for (int i = 0; i < NUM_ValueIndex; i++)
		{
			for (int j = 0; j < max_values - 1; j++)
				ring_buffer[i][j] = ring_buffer[i][j + 1];
		}
		ring_buffer[T_innen][max_values - 1] = read_innen_temperature();
		ring_buffer[F_innen][max_values - 1] = read_innen_humidity();
		ring_buffer[F_abs_innen][max_values - 1] = calculateAbsoluteHumidity(ring_buffer[T_innen][max_values - 1], ring_buffer[F_innen][max_values - 1]);
		ring_buffer[Helligkeit][max_values - 1] = read_LDR();
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
	Serial1.print(F("\n"));
}

void send_data_UART()
{
	static int count;
	count += Serial1.print(get_zyklus());
	count += Serial1.print(';');
	count += Serial1.print(timestamp_now_s());
	count += Serial1.print(';');
	count += printFloat_1digit(read_innen_temperature());
	count += Serial1.print(';');
	count += printFloat_1digit(read_innen_humidity());
	count += Serial1.print(';');
	count += printFloat_1digit(read_aussen_temperature());
	count += Serial1.print(';');
	count += printFloat_1digit(read_aussen_humidity());
	count += Serial1.print(';');
	count += printFloat_1digit(read_holz_temperature());
	count += Serial1.print(';');
	count += printFloat_1digit(read_holz_humidity());
	count += Serial1.print(';');
	count += printFloat_1digit(calculateAbsoluteHumidity(read_innen_temperature(), read_innen_humidity()));
	count += Serial1.print(';');
	count += Serial1.print(get_damper_state());
	count += Serial1.print(';');
	count += Serial1.print(get_fan_state());
	count += Serial1.print(';');
	count += Serial1.print(get_state());
	count += Serial1.print(';');
	count += Serial1.print(read_LDR());
	count += Serial1.print(';');
	count += Serial1.print(get_infotext());
	count += Serial1.print(';');
	count += Serial1.print('\n');
	if (count > 10000) //15000??
	{
		count = 0;
		create_new_file();
	}
	clear_infotext();
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

int printFloat_1digit(float f) { //ChatGPT
	int count;

	count = 0;	
	int ganz = (int)f;
  	int nachkomma = abs((int)(f * 10) % 10);
  	count += Serial1.print(ganz);
  	count += Serial1.print(',');
  	count += Serial1.print(nachkomma);
	return (count);
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

void create_new_file()
{
  // Low level triggers the save
  digitalWrite(pin_create_file, LOW);
  delay(500); // Duration of trigger
  digitalWrite(pin_create_file, HIGH);
}

int read_LDR() //LDR-Wert einlesen
{
	int ldrWert;

	ldrWert = analogRead(pin_LDR);   // LDR-Wert einlesen (0–1023) 
	return (ldrWert);
}

bool is_day() 
{
  	if (avarage_ringbuffer(Helligkeit,  3) > 800) // Schwellenwert für Tageslicht (anpassen je nach LDR)
		return (true); // Tag
	else
		return (false); // Nacht
}

void set_infotext(const char* msg)
{
    strncpy(infotext, msg, sizeof(infotext)-1);
    infotext[sizeof(infotext)-1] = '\0'; // sicherstellen, dass String terminiert ist
}

const char* get_infotext()
{
	return infotext;
}

void clear_infotext()
{
	infotext[0] = '\0'; // Setzt den String auf einen leeren Zustand
}