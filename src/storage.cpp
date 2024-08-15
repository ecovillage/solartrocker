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

int modus_adress = 0;
int pre_setup_adress = modus_adress + sizeof(int);

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

void print_storage()
{
	print_str_lcd("Modus:      ");
  	print_int_lcd(read_modus());
	print_str_lcd("\n");
}