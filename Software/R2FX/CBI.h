/**
  CBI.h - A library used to manage the CBI and DPL displays developed
  Micheal Erwin.  Big thanks to him and Glyn Harper for making this hardware
  continously available to club members.

  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

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
#include "R2FXConfig.h"
#include "VoltageDivider.h"

class CBI {
  private:
    CBI() {};
    CBI(CBI const&); // copy disabled
    void operator=(CBI const&); // assigment disabled
    LedControl lc = LedControl(SPI_DATA_PIN, SPI_CLOCK_PIN, SPI_CS_PIN, LC_NUM_DEVICES);
    unsigned long lastCBIUpdate = millis();
    unsigned long lastDPLUpdate = millis();
    char characters[26];
    bool hasCBIOn = false;
    bool hasDPLOn = false;
    VoltageDivider* vd = VoltageDivider::getInstance();

  public:
    static CBI* getInstance();
    
    void setup();

    enum DisplayState {
      RANDOM, SEQUENCE
    };

    DisplayState state = RANDOM;

    /**
    * Draws a random sequence on the CBI.
    */
    void randomCBISeq(int batLevel);

    /**
    * Draws a random sequence on the DPL
    */
    void randomDPLSeq();

    /**
    * Diplays the charge level on the LEDs.  The level must be between 0 and 100
    * Param:
    *   level    An int between 0 and 100
    */
    void displayChargeLevel(int level);

    /**
    * Turns on and off the CBI
    */
    void isCBIEnabled(bool enable);

    /**
    * Turns on and off the DPL
    */
    void isDPLEnabled(bool enable);

    /**
    * Gets the current state of the CBI display.
    */
    bool isCBIEnabled();

    bool isDPLEnabled();

    /**
    * Turns on/off every LED
    */
    void allOn(bool isOn);

    void heartSEQ();

    void loop();

};

#endif // CPI.h
