#include "Arduino.h"
#include "damper_logic.h"

size_t HUMIDITY    = 0;
size_t TEMPERATURE = 1;

/** Check whether we are on the "right" side of the curve. */
boolean air_too_moist(float air_humidity_inside, float air_temperature_inside) {
  // moisture vs temperature, stay below to keep heating
  size_t TABLE_SIZE = 3;

  float max_values_moisture_temperature[TABLE_SIZE][2] = {
    {10.0, 80.0},
    {20.0, 50.0},
    {30.0, 40.0}
  };

  /**
   * ^
   * |
   * humidity
   * |.X           OPEN
   * |...X         OPEN
   * |.....X       OPEN
   * |.........X   OPEN
   * |..CLOSE........x
   * +----------------temperature->
   */
  for (size_t i = 0; i < TABLE_SIZE; i++) {
    if (air_humidity_inside > max_values_moisture_temperature[i][HUMIDITY]) {
      return (air_temperature_inside > max_values_moisture_temperature[i][TEMPERATURE]);
    }
  }

  return false;
}
