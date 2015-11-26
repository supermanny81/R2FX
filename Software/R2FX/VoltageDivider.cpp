/**
  VoltageDivider.h - A library used to simplify determining battery and voltage levels.
  Copyright (c) 2015 Manny Garcia, written for the R2Builders group

  BSD license, all text above must be included in any redistribution
**/

#include "VoltageDivider.h"

VoltageDivider::VoltageDivider(int analogVin, float resistor1, float resistor2, float minVolts, float maxVolts) {
  ANALOG_VIN = analogVin;
  RESISTOR_1 = resistor1;
  RESISTOR_2 = resistor2;
  MIN_VOLTS = minVolts;
  MAX_VOLTS = maxVolts;
}

float VoltageDivider::getVCC() {
  float value = analogRead(ANALOG_VIN);
  int vout = (value * 5.00) / 1024.00;
  float vin = vout / (RESISTOR_2 / (RESISTOR_1 + RESISTOR_2));
  return vin;
}

int VoltageDivider::getVCCInPct() {
  float vin = getVCC();
  vin = vin == 0 ? MIN_VOLTS : vin;
  return ((vin - MIN_VOLTS) / (MAX_VOLTS - MIN_VOLTS)) * 100.0;
}
