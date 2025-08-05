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
int max_temp_adress = modus_adress + sizeof(int);
int zyklus_adress = max_temp_adress + sizeof(int);

// Funktion zum Speichern eines Wertes im EEPROM
void storeValueInEEPROM(int address, int value)
{
	EEPROM.put(address, value);  // Speichert den Wert im EEPROM an der angegebenen Adresse
}

void updateValueInEEPROM(int address, int value)
{
	EEPROM.update(address, value);  // Speichert den Wert im EEPROM an der angegebenen Adresse
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

int read_max_temp_EEPROM()
{
	return (readValueFromEEPROM(max_temp_adress));
}

void set_max_temp_EEPROM(int nb)
{
	storeValueInEEPROM(max_temp_adress, nb);
}

void save_max_temp()
{
	int	limit;
	int temperatur;

	limit = read_max_temp_EEPROM();
	temperatur = (int)read_innen_temperature();
	if (temperatur > limit + 1)
		set_max_temp_EEPROM(temperatur);
}

void reset_max_temp()
{
	set_max_temp_EEPROM(0);
}

void print_serial_storage()
{
	int	i;
	int	value;

	i = 0;
	while (i < 11)
	{
		EEPROM.get(i * sizeof(int), value);
		i++;
	}
}

void print_max_temp()
{
	print_str_lcd("max Temp:   ");
	print_int_lcd(read_max_temp_EEPROM());
	print_str_lcd(" ");
	print_char_lcd((char)247);                        // degree symbol
    print_str_lcd("C\n");
}

void increase_zyklus()
{
	storeValueInEEPROM(zyklus_adress, readValueFromEEPROM(zyklus_adress) + 1);
}

int get_zyklus()
{
	return (readValueFromEEPROM(zyklus_adress));
}

void set_zyklus(int nb)
{
	storeValueInEEPROM(zyklus_adress, nb);
}