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

class R2FXMessageHandler: public AbstractR2FXMessageHandler {

private:
  Adafruit_BluefruitLE_SPI ble = Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
  
  TimedServos* ts = TimedServos::getInstance();
  CBI* cbi = CBI::getInstance();
  VoltageDivider* vd = VoltageDivider::getInstance();
  
  void servoCommand(uint8_t board, uint8_t channel, char *buff, uint8_t pos,
      uint8_t nBytes);
  uint8_t toInt(char *arr, uint8_t pos, uint8_t nBytes);

public:
  void handleMessage(char *cmd);
  virtual void messageLoop();
};
#endif

