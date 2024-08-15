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
int readValueFromEEPROM(int address);
void set_modus(int nb);
int read_modus();
void print_storage();

#endif