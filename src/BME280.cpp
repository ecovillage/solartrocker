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
#include "BME280.h"
#include "Adafruit_BME280.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

void BME280_setup()
{
	Serial.println(F("BMP280 test"));
	if (!bme.begin())
		Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
	else
		Serial.println("BME280 OK");
}

float read_bme_temperature()
{
	return (bme.readTemperature()); // reads temperature in Celsius
}

float read_bme_humidity()
{
	return (bme.readHumidity()); // reads absolute humidity
}

float read_bme_pressure()
{
	return (bme.readPressure()); // reads pressure in hPa (hectoPascal = millibar)
}

float read_bme_altitude()
{
	return (bme.readAltitude(SEALEVELPRESSURE_HPA)); // estimates altitude in meters based on the pressure at the sea level.
}


//bme.readTemperature(); // reads temperature in Celsius;
//bme.readHumidity(); // reads absolute humidity;
//bme.readPressure(); // reads pressure in hPa (hectoPascal = millibar);
//bme.readAltitude(SEALEVELPRESSURE_HPA); // estimates altitude in meters based on the pressure at the sea level.