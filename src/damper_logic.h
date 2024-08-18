#ifndef _DAMPER_LOGIC_H
#define _DAMPER_LOGIC_H

boolean air_too_moist(float air_humidity_inside, float air_temperature_inside);
void check_humidity();
void check_fan_neccessary();

#endif