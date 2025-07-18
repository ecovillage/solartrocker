#ifndef _DAMPER_LOGIC_H
#define _DAMPER_LOGIC_H

boolean air_too_moist(float air_humidity_inside, float air_temperature_inside);
void state_auto();
void state_dehydrating();
void state_heating();
void state_const_hydrating();
void check_fan_neccessary();
void print_time_lueften();
unsigned long timestamp_now_s(void);
void set_state(int nb);
int get_state();
boolean is_hydrating_const();

#endif