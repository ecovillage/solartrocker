/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:34:39 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/15 08:34:39 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STORAGE_H
#define STORAGE_H

void storeValueInEEPROM(int address, int value);
void updateValueInEEPROM(int address, int value);
int readValueFromEEPROM(int address);
void set_modus(int nb);
int read_modus();
int read_max_temp_EEPROM(int limit);
void set_max_temp_EEPROM(int limit, int nb);
void save_max_temp();
void reset_max_temp();
void print_serial_storage();
void print_max_temp();
int get_zyklus();
void increase_zyklus();
void set_zyklus(int nb);


#endif