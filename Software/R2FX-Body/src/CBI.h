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
#include <LedControl.h>

/** Charge Bay and Data Port **/
//SPI Configuration for CBI and DPL
#define SPI_DATA_PIN 13
#define SPI_CLOCK_PIN 12
#define SPI_CS_PIN 11

//LED Control, one Maxim 72XX for each of the CBI and DPL, CBI must be first.
#define LC_NUM_DEVICES 2

//Brightness scale from 0 to 15
#define CBI_DISPLAY_INSTENSITY 8
#define CBI_DISPLAY_DELAY 500
#define DPL_DISPLAY_INSTENSITY 15
#define DPL_DISPLAY_DELAY 150

class CBI {
  private:
    CBI() {};
    CBI(CBI const&); // copy disabled
    void operator=(CBI const&); // assigment disabled

    LedControl lc = LedControl(SPI_DATA_PIN, SPI_CLOCK_PIN, SPI_CS_PIN, LC_NUM_DEVICES);
    unsigned long lastCBIUpdate = millis();
    unsigned long lastDPLUpdate = millis();
    bool hasCBIOn = false;
    bool hasDPLOn = false;
    byte voltagePct = 0x64; //100

  public:

    /**
     * Returns the instance of this class.  We want to prevent multiple copies of this class
     * being instatiated and taking memory.
     */
    static CBI* getInstance();

    /**
     * Used to configure the class, this should be called only once.
     */
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

    /**
     * Gets the current state of the Data Port Logics display.
     */
    bool isDPLEnabled();

    /**
    * Turns on/off every LED
    */
    void allOn(bool isOn);

    void heartSEQ();

    void setVoltage(byte percent);

    /**
     * Processes any updates to the CBI and DP using a cycle in the loop.
     */
    void loop();

};

#endif // CPI.h
