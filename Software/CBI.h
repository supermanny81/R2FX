/**
  CBI.h - A library used to manage the CBI and DPL displays.
  Copyright (c) 2015 Manny Garcia, written for the R2Builders group

  BSD license, all text above must be included in any redistribution
**/

#ifndef CPI_h
#define CPI_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "LedControl.h"
#include "BodyConfig.h"

class CBI {
  private:
    LedControl lc = LedControl(SPI_DATA_PIN, SPI_CLOCK_PIN, SPI_CS_PIN, LC_NUM_DEVICES);
    
  public:
    CBI();
    
    /**
    * Draws a random sequence on the CBI, and DPI.
    */
    void randomSeq(int batLevel);

    /**
    * Diplays the charge level on the LEDs.  The level must be between 0 and 100
    * Param:
    *   level    An int between 0 and 100
    */
    void displayChargeLevel(int level);
    
    void enabled(bool isEnabled);
    
    void allOn();
    void heartSEQ();

};

#endif // CPI.h

