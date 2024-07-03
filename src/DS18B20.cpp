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
#include <OneWire.h>
#include <DallasTemperature.h>
//#include "Wire.h"

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

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

//sensors.requestTemperatures(); //call before getting the actual temperature value
//sensors.getTempCByIndex(0); //To get the temperature in Celsius
//sensors.getDeviceCount();// Grab a count of devices on the wire