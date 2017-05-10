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
  switch (cmd) {
    case R2FXCommand::CBI_DPL_DISABLE:
      cbi->allOn(false);
      Log.notice(F("Disabling CBI & DPL." CR));
      break;
    case R2FXCommand::CBI_DPL_ENABLE:
      cbi->allOn(true);
      Log.notice(F("Enabling CBI & DPL." CR));
      break;
    case R2FXCommand::DPL_DISABLE:
      cbi->isDPLEnabled(false);
      Log.notice(F("Disabling DPL." CR));
      break;
    case R2FXCommand::DPL_ENABLE:
      cbi->isDPLEnabled(true);
      Log.notice(F("Enabling DPL." CR));
      break;
    case R2FXCommand::CBI_DISABLE:
      cbi->isCBIEnabled(false);
      Log.notice(F("Disabling CBI." CR));
      break;
    case R2FXCommand::CBI_ENABLE:
      cbi->isCBIEnabled(true);
      Log.notice(F("Enabling CBI." CR));
      break;
    case R2FXCommand::CBI_HEART_SEQ:
      cbi->heartSEQ();
      Log.notice(F("Playing heart sequence." CR));
      break;
    case R2FXCommand::CBI_DISPLAY_VOLTAGE:
      if (nBytes > 1) {
        byte voltage = Wire.read();
        cbi->setVoltage(voltage);
      }
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
