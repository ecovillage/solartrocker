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

#ifndef FAN_H
#define FAN_H

void fan_setup();

void fan_on();
void fan_off();
int fan_state();
void print_state_fan();

#endif