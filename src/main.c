#include <Arduino.h>

#include "fan.h"

const int pin_Endschalter = 2; 
const int pin_Motor = 14;

void damper_motor_off()
{
	digitalWrite(pin_Motor, LOW);
}

void setup() {
  // put your setup code here, to run once:
  fan_setup();
  pinMode(pin_Endschalter, INPUT_PULLUP); //Verschieben zu dampers.c!

  attachInterrupt(digitalPinToInterrupt(pin_Endschalter), damper_motor_off, FALLING); //in dampers_setup verschieben!
}

void loop() {
  // put your main code here, to run repeatedly:
}

