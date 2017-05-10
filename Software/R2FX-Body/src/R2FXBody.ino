#include <Arduino.h>
#include <ArduinoLog.h>
#include <LedControl.h>
#include <Wire.h>

#include "CBI.h"
#include "Dome.h"
#include "R2FXEnums.h"

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
  R2FXCommand cmd = (R2FXCommand) Wire.read();
  if (nBytes < 2) {
    Log.fatal(F("Required paramters were missing from the command." CR));
    return;
  }

  byte val = Wire.read();
  switch (cmd) {
    case R2FXCommand::CBI_DPL_ENABLED:
      cbi->allOn((bool) val);
      Log.notice(F("CBI & DPL enabled (%b)." CR), val);
      break;
    case R2FXCommand::DPL_ENABLED:
      cbi->isDPLEnabled(val);
      Log.notice(F("DPL enabled (%b)." CR), val);
      break;
    case R2FXCommand::CBI_ENABLED:
      cbi->isCBIEnabled(val);
      Log.notice(F("CBI enabled (%b)." CR), val);
      break;
    case R2FXCommand::CBI_SEQ:
      if (val == 1) {
        cbi->heartSEQ();
        Log.notice(F("Playing heart sequence." CR));
      }
      break;
    case R2FXCommand::CBI_VOLTAGE:
      cbi->setVoltage(val);
      break;
    default:
      Log.notice(F("Unknown command: %d" CR), cmd);
      break;
  }
}

void requestEvent() {
  while (Wire.available()) {
    R2FXCommand cmd = (R2FXCommand) Wire.read();
    switch (cmd) {
      case R2FXCommand::DOME_POSITION:
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
