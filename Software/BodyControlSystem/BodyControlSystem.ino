#include <Adafruit_PWMServoDriver.h>
#include "LedControl.h"
#include "elapsedMillis.h"
#include "Wire.h"
#include "CBI.h"
#include "VoltageDivider.h"
#include "CommandParser.h"
#include "BodyConfig.h"
#include "Utility.h"
#include "TimedServos.h"


CommandParser cmd = CommandParser();
CBI cbi = CBI();
TimedServos ts = TimedServos();      
VoltageDivider vd = VoltageDivider(VD_ANALOG_VIN_PIN, VD_RESISTOR_1,
                                   VD_RESISTOR_2, VD_MIN_VOLTAGE, 
                                   VD_MAX_VOLTAGE);
         
                                  
void setup() {
  // initialize random seed with reading from a PIN that is not used.
  // randomSeed(analogRead(ANALOG_PIN_SEED));
  // Used for debugging
  Serial.begin(SERIAL_BAUD_RATE);
  cmd.clearCommand();
  Serial.println(F("Body Control Version 1.0"));
  ts.setup();
}

void cmdLoop() {
  if (cmd.hasCommand()) {
    const char *response = {'\0'};
    byte exitCode = 0;
    
    switch (cmd.commandBuffer[0]) {
      case 'C': {
        switch (cmd.commandBuffer[1]) {
          case 'L': { cbi.isCBIEnabled(!cbi.isCBIEnabled()); break;}
          case 'R': { cbi.isDPLEnabled(!cbi.isDPLEnabled()); break;}
          case 'H': {
            // temp sequence
            bool tmp = cbi.isCBIEnabled();
            cbi.isCBIEnabled(true);
            cbi.heartSEQ();
            cbi.isCBIEnabled(tmp);
            break;
          }
          case 'S': {response = (cbi.isCBIEnabled() ? "True":"False"); break;}
          default: exitCode = 2;
        }
        break;
      }
      case 'U': {
        switch (cmd.commandBuffer[1]) {
          case '1': {response = "U1"; ts.setServoPosition(0, 1, 180, 2000); break;}
          case '2': {response = "U2"; ts.setServoPosition(0, 1, 0, 0); break;}
          case '3': {response = "U3"; ; break;}
        }
        break;
      }
      case 'V': {
        switch (cmd.commandBuffer[1]) {
          case 'P': {char buff[5]; response = FloatToString(buff, vd.getVCCInPct(), 2, 0); break; }
          case 'D': {char buff[5]; response = FloatToString(buff, vd.getVCC(), 2, 0); break; }
          default:  exitCode = 2;
        }
        break;
      }
      default: exitCode = 2;
    }

    // return exit code and clean up
    cmd.returnStatus(exitCode, response);
    cmd.clearCommand();
  }
}

void cbiLoop() {
  if (cbi.isCBIEnabled()) {
    cbi.randomCBISeq(vd.getVCCInPct());
  }
  if (cbi.isDPLEnabled()) {
     cbi.randomDPLSeq();
  }
}

void loop() {
  cmdLoop();
  cbiLoop();
  ts.processMovements();
}
