/**
 CommandHandler - A library for processesing commands.

 Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

 BSD license, all text above must be included in any redistribution
 **/

#ifndef Command_Handler_h
#define Command_Handler_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "R2FXconfig.h"
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include "TimedServos.h"
#include "VoltageDivider.h"
#include "CBI.h"
#include "Utility.h"
#include "AbstractR2FXMessageHandler.h"
#include "MemFree.h"

class R2FXMessageHandler: public AbstractR2FXMessageHandler {
  public:
    virtual void loop();

  private:
    Adafruit_BluefruitLE_SPI ble = Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
    TimedServos* ts = TimedServos::getInstance();
    CBI* cbi = CBI::getInstance();
    VoltageDivider* vd = VoltageDivider::getInstance();

    /**
     * Dome Systems
     */
    virtual void setDomePpcPos(byte pos, int duration); // center pie panel
    virtual void setDomePp1Pos(byte pos, int duration); // pie panel 1
    virtual void setDomePp2Pos(byte pos, int duration); // pie panel 2
    virtual void setDomePp5Pos(byte pos, int duration); // pie panel 5
    virtual void setDomePp6Pos(byte pos, int duration); // pie panel 6

    virtual void setDomeP1Pos(byte pos, int duration); // panel 1
    virtual void setDomeP2Pos(byte pos, int duration); // panel 2
    virtual void setDomeP3Pos(byte pos, int duration); // panel 3
    virtual void setDomeP4Pos(byte pos, int duration); // panel 4
    virtual void setDomeP7Pos(byte pos, int duration); // panel 7
    virtual void setDomeP10Pos(byte pos, int duration); // panel 10
};
#endif
