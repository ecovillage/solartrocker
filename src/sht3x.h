/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sht3x.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:07:47 by jweingar          #+#    #+#             */
/*   Updated: 2025/07/26 13:07:47 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHT3X_H
#define SHT3X_H

#include <Arduino.h>

void SHT3X_setup();

float read_sht3x_temperature(uint8_t address);
float read_sht3x_humidity(uint8_t address);

float read_aussen_temperature();
float read_aussen_humidity();

float read_holz_temperature();
float read_holz_humidity();

void print_values_SHT3X();

#endif // SHT3X_H
