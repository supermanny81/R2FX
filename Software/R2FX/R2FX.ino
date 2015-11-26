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
  randomSeed(analogRead(ANALOG_PIN_SEED));
  // Used for debugging
  Serial.begin(SERIAL_BAUD_RATE);
  cmd.clearCommand();
  Serial.println(F("R2FX v1.1"));
  ts.setup();
  // Use fast IIC
  TWBR = 12; // upgrade to 400KHz!
}

void processCmdInput() {
  if (cmd.hasCommand()) {
    const char *response = {'\0'};
    byte exitCode = 0;

    switch (cmd.commandBuffer[0]) {
      // Dome Panels
      case 'P': {
          switch (cmd.commandBuffer[1]) {
            // Pie Panels
            case 'P': {
                switch (cmd.commandBuffer[2]) {
                  case 'C' : {
                      servoCommand(1, SV_PPC, cmd.commandBuffer, 3, 3);
                      response = "PPC";
                      break;
                    }
                  case '1' : {
                      servoCommand(1, SV_PP1, cmd.commandBuffer, 3, 3);
                      response = "PP1";
                      break;
                    }
                  case '2' : {
                      servoCommand(1, SV_PP2, cmd.commandBuffer, 3, 3);
                      response = "PP2";
                      break;
                    }
                  case '5' : {
                      servoCommand(1, SV_PP5, cmd.commandBuffer, 3, 3);
                      response = "PP5";
                      break;
                    }
                  case '6' : {
                      servoCommand(1, SV_PP6, cmd.commandBuffer, 3, 3);
                      response = "PP6";
                      break;
                    }
                }
                break;
              }
            case '1': {
                servoCommand(1, SV_P1, cmd.commandBuffer, 3, 3);
                response = "P1";
                break;
              }
            case '2': {
                servoCommand(1, SV_P2, cmd.commandBuffer, 3, 3);
                response = "P2";
                break;
              }
            case '3': {
                servoCommand(1, SV_P3, cmd.commandBuffer, 3, 3);
                response = "P3";
                break;
              }
            case '4': {
                servoCommand(1, SV_P4, cmd.commandBuffer, 3, 3);
                response = "P4";
                break;
              }
            case '7': {
                servoCommand(1, SV_P7, cmd.commandBuffer, 3, 3);
                response = "P7";
                break;
              }
            case 'A': {
                servoCommand(1, SV_PA, cmd.commandBuffer, 3, 3);
                response = "PA";
                break;
              }

          }
          break;
        }
      // Check voltage levels
      case 'V': {
          switch (cmd.commandBuffer[1]) {
            case 'P': {
                char buff[5];
                response = FloatToString(buff, vd.getVCCInPct(), 2, 0);
                break;
              }
            case 'D': {
                char buff[5];
                response = FloatToString(buff, vd.getVCC(), 2, 0);
                break;
              }
          }
          break;
        }
      case 'C': {
          switch (cmd.commandBuffer[1]) {
            case 'L': {
                cbi.isCBIEnabled(!cbi.isCBIEnabled());
                break;
              }
            case 'R': {
                cbi.isDPLEnabled(!cbi.isDPLEnabled());
                break;
              }
            case 'H': {
                // temp sequence
                bool tmp = cbi.isCBIEnabled();
                cbi.isCBIEnabled(true);
                cbi.heartSEQ();
                cbi.isCBIEnabled(tmp);
                break;
              }
            case 'S': {
                response = (cbi.isCBIEnabled() ? "True" : "False");
                break;
              }
          }
          break;
        }
      case 'U': {
          switch (cmd.commandBuffer[1]) {
            case '1': {
                response = "U1";
                ts.setServoPosition(0, 1, 180, 2000);
                break;
              }
            case '2': {
                response = "U2";
                ts.setServoPosition(0, 1, 0, 0);
                break;
              }
            case '3': {
                response = "U3"; ;
                break;
              }
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

void servoCommand(uint8_t board, uint8_t channel, char *buff, uint8_t pos, uint8_t nBytes) {
  uint8_t svPos = toInt(buff, 3, nBytes);
  ts.setServoPosition(board, channel, svPos, 0);
}

uint8_t toInt(char *arr, uint8_t pos, uint8_t nBytes) {
  String work = String();
  for (uint8_t i = 0; i < nBytes; i++) {
    work += String(arr[pos + i] - '0');
  }
  return work.toInt();
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
  processCmdInput();
  cbiLoop();
  ts.processMovements();
}
