/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DS18B20.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:38:42 by jweingar          #+#    #+#             */
/*   Updated: 2024/07/03 11:38:42 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include "ds18B20.h"
#include "lcd.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 8

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void DS18B20_setup()
{
  // Start up the library
  sensors.begin();
}

float read_temp(int index)
{
	sensors.requestTemperatures(); //call before getting the actual temperature value
	return (sensors.getTempCByIndex(index)); //To get the temperature in Celsius
}

void print_values_DS18B20()
{
    print_str_lcd("T(DS):      ");
    print_float_lcd(read_temp(0));
    print_str_lcd(" ");
	print_char_lcd((char)247);                        // degree symbol
    print_str_lcd("C\n");
}

//sensors.requestTemperatures(); //call before getting the actual temperature value
//sensors.getTempCByIndex(0); //To get the temperature in Celsius
//sensors.getDeviceCount();// Grab a count of devices on the wire