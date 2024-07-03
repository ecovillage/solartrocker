#ifndef BME280_H
#define BME280_H

void BME280_setup();

float read_bme_temperature();
float read_bme_humidity();
float read_bme_pressure();
float read_bme_altitude();

#endif