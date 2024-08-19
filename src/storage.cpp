/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:34:43 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/15 08:34:43 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include <EEPROM.h>
#include "storage.h"
#include "lcd.h"
#include "bme280.h"

int modus_adress = 0;
int max20_adress = modus_adress + sizeof(int);
int max30_adress = max20_adress + sizeof(int);
int max40_adress = max30_adress + sizeof(int);
int max50_adress = max40_adress + sizeof(int);
int max60_adress = max50_adress + sizeof(int);
int max70_adress = max60_adress + sizeof(int);
int max80_adress = max70_adress + sizeof(int);

// Funktion zum Speichern eines Wertes im EEPROM
void storeValueInEEPROM(int address, int value)
{
	EEPROM.put(address, value);  // Speichert den Wert im EEPROM an der angegebenen Adresse
}

// Funktion zum Lesen des Wertes aus dem EEPROM
int readValueFromEEPROM(int address)
{
	int value;
	EEPROM.get(address, value);  // Liest den Wert aus dem EEPROM an der angegebenen Adresse
	return (value);
}

void set_modus(int nb)
{
	storeValueInEEPROM(modus_adress, nb);
}

int read_modus()
{
	return (readValueFromEEPROM(modus_adress));
}

int read_limit(int limit)
{
	return (readValueFromEEPROM((limit / 10 - 1) * sizeof(int)));
}

void set_limit(int limit, int nb)
{
	storeValueInEEPROM((limit / 10 - 1) * sizeof(int), nb);
}

void save_max_temp()
{
	int	limit;

	limit = 20;
	while (limit < 90)
	{
		if (read_bme_temperature() > limit && read_limit(limit) == 0)
			set_limit(limit, 1);
		limit += 10;
	}
}

int calc_max_temp()
{
	int	limit;
	int max_temp;

	limit = 20;

	while (limit < 90)
	{
		if (read_limit(limit) == 1)
			max_temp = limit;
		limit += 10;
	}
	return (max_temp);
}

void reset_max_temp()
{
	int	limit;

	limit = 20;
	while (limit < 90)
	{
		set_limit(limit, 0);
		limit += 10;
	}
}

void print_serial_storage()
{
	int	i;
	int	value;

	i = 0;
	while (i < 11)
	{
		EEPROM.get(i * sizeof(int), value);
		Serial.print(value);
		Serial.print(", ");
		i++;
	}
	Serial.print("\n");
}

void print_storage()
{
	print_str_lcd("max Temp >  ");
	print_int_lcd(calc_max_temp());
	print_str_lcd("\n");
}