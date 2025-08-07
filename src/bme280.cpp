/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BME280.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:28:45 by jweingar          #+#    #+#             */
/*   Updated: 2024/07/03 11:28:45 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Arduino.h>
#include "bme280.h"
#include "Adafruit_BME280.h"
#include "lcd.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme_innen; // I2C
Adafruit_BME280 bme_aussen; // I2C

void BME280_setup()
{
	bme_innen.begin(0x76);
	bme_aussen.begin(0x77);
}

float read_innen_temperature()
{
	return (bme_innen.readTemperature()); // reads temperature in Celsius
}

float read_innen_humidity()
{
	return (bme_innen.readHumidity()); // reads absolute humidity
}

float read_aussen_temperature()
{
   return (bme_aussen.readTemperature()); // reads temperature in Celsius
}

float read_aussen_humidity()
{
    return (bme_aussen.readHumidity()); // reads absolute humidity
}

void print_values_BME280()
{
    print_str_lcd("T(innen):   "); 
    print_float_lcd(read_innen_temperature());
    print_str_lcd(" 'C\n");
	
	print_str_lcd("F(innen):   "); 
    print_float_lcd(read_innen_humidity());
    print_str_lcd(" %\n");

	print_str_lcd("T(aussen):  "); 
    print_float_lcd(read_aussen_temperature());
    print_str_lcd(" 'C\n");
	
	print_str_lcd("F(aussen):  "); 
    print_float_lcd(read_aussen_humidity());
    print_str_lcd(" %\n");
}