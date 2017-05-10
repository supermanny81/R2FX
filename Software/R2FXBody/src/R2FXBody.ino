#include <ArduinoLog.h>
#include <LedControl.h>
#include <Wire.h>

#include "CBI.h"
#include "Dome.h"

#define VERSION "0.0.1"
#define BODY_FX_ADDRESS 0x08

CBI* cbi = CBI::getInstance();
Dome* dome = Dome::getInstance();

void setup() {
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
  Log.verbose(F("R2FX: Body Control v%s" CR), VERSION);
  cbi->setup();

  Wire.begin(BODY_FX_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  cbi->loop();
  dome->loop();
}

void receiveEvent(int nBytes) {
  while (1 < Wire.available()) {
    byte cmd = Wire.read();
    switch (cmd) {
      case 0x00: //0
        cbi->allOn(false);
        Log.notice(F("Disabling CBI & DPL." CR));
        break;
      case 0x01: //1
        cbi->allOn(true);
        Log.notice(F("Enabling CBI & DPL." CR));
        break;
      case 0x05: //5
        cbi->isDPLEnabled(false);
        Log.notice(F("Disabling DPL." CR));
        break;
      case 0x06: //6
        cbi->isDPLEnabled(true);
        Log.notice(F("Enabling DPL." CR));
        break;
      case 0x0A: //10
        cbi->isCBIEnabled(false);
        Log.notice(F("Disabling CBI." CR));
        break;
      case 0x0B: //11
        cbi->isCBIEnabled(true);
        Log.notice(F("Enabling CBI." CR));
        break;
      case 0x0C: //12
        cbi->heartSEQ();
        Log.notice(F("Playing heart sequence." CR));
        break;
      case 0x0D: //13
        if (1 < Wire.available()) {
          byte voltage = Wire.read();
          cbi->setVoltage(voltage);
        }
        break;
      default:
        Log.notice(F("Unknown command: %d" CR), cmd);
        break;
    }
  }
}

void requestEvent() {
    while (1 < Wire.available()) {
    byte cmd = Wire.read();
    switch (cmd) {
      case 0x14: //20
        Wire.write(dome->getDomePosition());
        Log.notice(F("Dome position: %d" CR), dome->getDomePosition());
        break;
      default:
        Wire.write(-1);
        Log.notice(F("Unknown command: %d" CR), cmd);
        break;
    }
  }
}
