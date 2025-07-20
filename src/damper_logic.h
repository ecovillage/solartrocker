#ifndef _DAMPER_LOGIC_H
#define _DAMPER_LOGIC_H

bool air_too_moist(float air_humidity_inside, float air_temperature_inside);
void state_auto();
void state_dehydrating();
void state_heating();
void state_RF_const();
void state_menue();
void check_fan_neccessary();
void print_time_lueften();
unsigned long timestamp_now_s(void);
void set_state(int nb);
int get_state();
bool is_hydrating_const();
void set_state_auto();
void set_state_lueften();
void set_state_heizen();
void set_state_RF_const();
void set_state_menue();

#endif