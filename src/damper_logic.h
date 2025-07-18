#ifndef _DAMPER_LOGIC_H
#define _DAMPER_LOGIC_H

boolean air_too_moist(float air_humidity_inside, float air_temperature_inside);
void check_hydrating();
void check_fan_neccessary();
void print_time_lueften();
void set_status_lueften();
void set_status_normal();
void set_status_humidity_konstant();
unsigned long timestamp_now_s(void);

#endif