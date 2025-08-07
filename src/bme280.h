#ifndef BME280_H
#define BME280_H

void BME280_setup();

float read_innen_temperature();
float read_innen_humidity();
float read_aussen_temperature();
float read_aussen_humidity();
float read_bme_pressure();
float read_bme_altitude();
void print_values_BME280();

#endif