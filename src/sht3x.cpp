/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sht3x.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:07:39 by jweingar          #+#    #+#             */
/*   Updated: 2025/07/26 13:07:39 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Arduino.h>
#include "sht3x.h"
#include <Wire.h>
#include "lcd.h"

#define SHT3X_AUSSEN 0x45
#define SHT3X_HOLZ   0x44

const uint8_t cmd_measure[2] = {0x24, 0x00};

void SHT3X_setup()
{
    Wire.begin();
}

static bool read_raw_sht(uint8_t address, uint16_t* temp_raw, uint16_t* hum_raw)
{
    Wire.beginTransmission(address);
    Wire.write(cmd_measure, 2);
    Wire.endTransmission();

    delay(15);

    Wire.requestFrom(address, (uint8_t)6);
    if (Wire.available() != 6)
        return false;

    *temp_raw = (Wire.read() << 8) | Wire.read();
    Wire.read(); // CRC ignored
    *hum_raw = (Wire.read() << 8) | Wire.read();
    Wire.read(); // CRC ignored

    return true;
}

float read_sht3x_temperature(uint8_t address)
{
    uint16_t t_raw, h_raw;
    if (!read_raw_sht(address, &t_raw, &h_raw))
        return (NAN);
    return (-45 + 175 * (t_raw / 65535.0));
}

float read_sht3x_humidity(uint8_t address)
{
    uint16_t t_raw, h_raw;
    if (!read_raw_sht(address, &t_raw, &h_raw))
        return (NAN);
    return (100 * (h_raw / 65535.0));
}

float read_aussen_temperature()
{
    return (read_sht3x_temperature(SHT3X_AUSSEN));
}

float read_aussen_humidity()
{
    return (read_sht3x_humidity(SHT3X_AUSSEN));
}

float read_holz_temperature()
{
    return (read_sht3x_temperature(SHT3X_HOLZ));
}

float read_holz_humidity()
{
    return (read_sht3x_humidity(SHT3X_HOLZ));
}

void print_values_SHT3X()
{
    print_str_lcd("T(aussen):  "); 
    print_float_lcd(read_aussen_temperature());
    print_str_lcd(" °C\n");
	
	print_str_lcd("F(aussen):  "); 
    print_float_lcd(read_aussen_humidity());
    print_str_lcd(" %RH\n");

	print_str_lcd("T(Holz):    "); 
    print_float_lcd(read_holz_temperature());
    print_str_lcd(" °C\n");
	
	print_str_lcd("F(Holz):    "); 
    print_float_lcd(read_holz_humidity());
    print_str_lcd(" %RH\n");
}
