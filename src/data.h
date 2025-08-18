/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:19:43 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/18 14:19:43 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
#define DATA_H

enum ValueIndex {
    T_innen,
	F_innen,
    F_abs_innen,
    NUM_ValueIndex  // entspricht x + 1, wichtig für Schleifen etc.
};

void data_setup();
void collect_data();
float avarage_ringbuffer(int value);
float avarage_humidity_bme();
float delta_min_max_abs_humidity();
void send_data_UART();
float saturation_vapor_pressure(float temperature);
float calculateAbsoluteHumidity(float temperature, float relativeHumidity);
float calculatePineEMC(float temperature, float relativeHumidity);
float* get_ring_buffer(int i);
int get_max_values();
float min_array(float *arr, const int size);
float max_array(float *arr, const int size);
bool is_first_round();
float humidity_changed_temperature(float t_begin, float h_begin, float t_end);
void send_headline_UART();
void printFloat_1digit(float f);
int freeMemory();
void create_new_file();
bool is_day();


#endif