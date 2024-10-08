/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fan.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:03:37 by jweingar          #+#    #+#             */
/*   Updated: 2024/07/03 15:03:37 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DS18B20_H
#define DS18B20_H

void DS18B20_setup();

float read_temp(int index);
void print_values_DS18B20();

#endif