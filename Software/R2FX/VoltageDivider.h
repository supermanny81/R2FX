/**
  VoltageDivider.h - A library used to simplify determining battery and voltage levels.
  Copyright (c) 2015 Manny Garcia, written for the R2Builders group

  BSD license, all text above must be included in any redistribution
**/

#ifndef VoltageDivider_h
#define VoltageDivider_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class VoltageDivider {

  public:

    /**
    * Creates a new voltage divider.
    * Params:
    * analogVin:    Reads in analog value (0 ... 1024) from the supply
    *               (if it is greater than 5v, resisters must be used)
    * resitor1      For 15v and 30v systems, use 47k.
    * resistor2     For 15v use 24k, for 30v use 9.4k
    * minVolts      Discharged battery voltage
    * maxVolts      Fully charged battery voltage
    */
    VoltageDivider(int analogVin, float resistor1, float resistor2, float minVolts, float maxVolts);

    /**
    * Returns the measured voltage from the supply
    */
    float getVCC();

    /**
    * Returns the measured voltage from the supply in percentage, min and max voltages 
    * must be set for this reading to be accurate
    */
    int getVCCInPct();

  private:
    byte ANALOG_VIN;
    float RESISTOR_1;
    float RESISTOR_2;
    float MIN_VOLTS;
    float MAX_VOLTS;

};

#endif // VoltageDivider.h
