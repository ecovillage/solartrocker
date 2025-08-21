#ifndef _DAMPER_LOGIC_H
#define _DAMPER_LOGIC_H

enum stateIndex {
    Auto,
	Lueften,
	Heizen,
	RF_const,
	Manuel,
	Night,
    NUM_stateIndex  // entspricht x + 1, wichtig für Schleifen etc.
};

void setup_damper_logic();
void set_f_a_innen_close_damper();
void add_to_summe_wasser();
bool air_too_moist(float air_humidity_inside, float air_temperature_inside);
void state_auto();
void set_state_manuel();
void state_dehydrating();
void state_heating();
void state_RF_const();
void state_night();
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
void set_state_night();
void set_state_menue();
void state_manuel();

#endif