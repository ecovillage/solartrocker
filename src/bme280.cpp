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

Adafruit_BME280 bme; // I2C

void BME280_setup()
{
	bme.begin(0x76);
}

float read_innen_temperature()
{
	return (bme.readTemperature()); // reads temperature in Celsius
}

float read_innen_humidity()
{
	return (bme.readHumidity()); // reads absolute humidity
}

void print_values_BME280()
{
    print_str_lcd("T(innen):   "); 
    print_float_lcd(read_innen_temperature());
    print_str_lcd(" °C\n");
	
	print_str_lcd("F(innen):   "); 
    print_float_lcd(read_innen_humidity());
    print_str_lcd(" %RH\n");
}
