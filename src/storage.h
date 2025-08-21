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

void storeIntInEEPROM(int address, int value);
void updateIntInEEPROM(int address, int value);
int readIntFromEEPROM(int address);
void storeFloatInEEPROM(int address, float value);
void updateFloatInEEPROM(int address, float value);
float readFloatFromEEPROM(int address);
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
float get_summe_wasser();
void set_summe_wasser(float nb);
void reset_summe_wasser();
void print_summe_wasser();


#endif