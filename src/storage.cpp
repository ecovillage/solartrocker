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

int		modus_adress = 0;
int		max_temp_adress = modus_adress + sizeof(int);
int		zyklus_adress = max_temp_adress + sizeof(int);
int		summe_wasser_adress = zyklus_adress + sizeof(int);
int		next = summe_wasser_adress + sizeof(float);

// Funktion zum Speichern eines Wertes im EEPROM
void storeIntInEEPROM(int address, int value)
{
	EEPROM.put(address, value);  // Speichert den Wert im EEPROM an der angegebenen Adresse
}

void updateIntInEEPROM(int address, int value)
{
	EEPROM.update(address, value);  // Speichert den Wert im EEPROM an der angegebenen Adresse
}

// Funktion zum Lesen des Wertes aus dem EEPROM
int readIntFromEEPROM(int address)
{
	int value;
	EEPROM.get(address, value);  // Liest den Wert aus dem EEPROM an der angegebenen Adresse
	return (value);
}

void storeFloatInEEPROM(int address, float value)
{
    EEPROM.put(address, value);  // Speichert den float-Wert im EEPROM
}

// Funktion zum Aktualisieren eines float-Wertes im EEPROM
void updateFloatInEEPROM(int address, float value)
{
    EEPROM.update(address, value);  // Aktualisiert den float-Wert im EEPROM
}

// Funktion zum Lesen eines float-Wertes aus dem EEPROM
float readFloatFromEEPROM(int address)
{
    float value;
    EEPROM.get(address, value);  // Liest den float-Wert aus dem EEPROM
    return value;
}

void set_modus(int nb)
{
	storeIntInEEPROM(modus_adress, nb);
}

int read_modus()
{
	return (readIntFromEEPROM(modus_adress));
}

int read_max_temp_EEPROM()
{
	return (readIntFromEEPROM(max_temp_adress));
}

void set_max_temp_EEPROM(int nb)
{
	storeIntInEEPROM(max_temp_adress, nb);
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
	storeIntInEEPROM(zyklus_adress, readIntFromEEPROM(zyklus_adress) + 1);
}

int get_zyklus()
{
	return (readIntFromEEPROM(zyklus_adress));
}

void set_zyklus(int nb)
{
	storeFloatInEEPROM(zyklus_adress, nb);
}

float get_summe_wasser()
{
	return (readFloatFromEEPROM(summe_wasser_adress));
}

void set_summe_wasser(float nb)
{
	storeFloatInEEPROM(summe_wasser_adress, nb);
}

void reset_summe_wasser()
{
	storeFloatInEEPROM(summe_wasser_adress, 0);
}

void print_summe_wasser()
{
	print_str_lcd("Sum_Wasser: ");
	print_float_lcd(get_summe_wasser());
	print_str_lcd(" g");

}



