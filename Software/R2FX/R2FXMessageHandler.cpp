
#include "R2FXMessageHandler.h"

void R2FXMessageHandler::handleMessage(char *cmd) {
  const char *response;
  switch (cmd[0]) {
    // Dome Panels
    case 'P': {
        switch (cmd[1]) {
          // Pie Panels
          case 'P': {
              switch (cmd[2]) {
                case 'C': {
                    servoCommand(1, SV_PPC, cmd, 3, 3);
                    response = PSTR("PPC");
                    break;
                  }
                case '1': {
                    servoCommand(1, SV_PP1, cmd, 3, 3);
                    response = PSTR("PP1");
                    break;
                  }
                case '2': {
                    servoCommand(1, SV_PP2, cmd, 3, 3);
                    response = PSTR("PP2");
                    break;
                  }
                case '5': {
                    servoCommand(1, SV_PP5, cmd, 3, 3);
                    response = PSTR("PP5");
                    break;
                  }
                case '6': {
                    servoCommand(1, SV_PP6, cmd, 3, 3);
                    response = PSTR("PP6");
                    break;
                  }
              }
              break;
            }
          case '1': {
              servoCommand(1, SV_P1, cmd, 2, 3);
              response = PSTR("P1");
              break;
            }
          case '2': {
              servoCommand(1, SV_P2, cmd, 2, 3);
              response = PSTR("P2");
              break;
            }
          case '3': {
              servoCommand(1, SV_P3, cmd, 2, 3);
              response = PSTR("P3");
              break;
            }
          case '4': {
              servoCommand(1, SV_P4, cmd, 2, 3);
              response = PSTR("P4");
              break;
            }
          case '7': {
              servoCommand(1, SV_P7, cmd, 2, 3);
              response = PSTR("P7");
              break;
            }
          case 'A': {
              servoCommand(1, SV_PA, cmd, 2, 3);
              response = PSTR("PA");
              break;
            }

        }
        break;
      }
    // Body Commands
    case 'C': {
        switch (cmd[1]) {
          case 'B': {
              cbi->isCBIEnabled(!cbi->isCBIEnabled());
              response = (
                           cbi->isCBIEnabled() ? PSTR("CB: True") : PSTR("CB: False"));
              break;
            }
          case 'R': {
              cbi->isDPLEnabled(!cbi->isDPLEnabled());
              break;
            }
          case 'H': {
              // temp sequence
              bool tmp = cbi->isCBIEnabled();
              cbi->isCBIEnabled(true);
              cbi->heartSEQ();
              cbi->isCBIEnabled(tmp);
              break;
            }
        }
        break;
      }
    case 'D': {
        switch (cmd[1]) {
          case 'P': {
              cbi->isDPLEnabled(!cbi->isDPLEnabled());
              response = (
                           cbi->isDPLEnabled() ? PSTR("DP: True") : PSTR("DP: False"));
              break;
            }
        }
        break;
      }
    case 'U': {
        switch (cmd[1]) {
          case 'T': {
              servoCommand(0, SV_UA_TOP, cmd, 2, 3);
              response = PSTR("UT");
              break;
            }
          case 'B': {
              servoCommand(0, SV_UA_BOTTOM, cmd, 2, 3);
              response = PSTR("UB");
              break;
            }
        }
        break;
      }
    // System Commands
    // Check voltage levels
    case 'V': {
        switch (cmd[1]) {
          case 'P': {
              char buff[5];
              Utility util = Utility();
              response = util.floatToString(buff, vd->getVCCInPct(), 2, 0);
              break;
            }
          case 'D': {
              char buff[5];
              Utility util = Utility();
              response = util.floatToString(buff, vd->getVCC(), 2, 0);
              break;
            }
        }
        break;
      }
      //default: exitCode = 2;
  }
}

void R2FXMessageHandler::servoCommand(uint8_t board, uint8_t channel,
                                      char *buff, uint8_t pos, uint8_t nBytes) {
  uint8_t svPos = toInt(buff, 3, nBytes);
  ts->setServoPosition(board, channel, svPos, 0);
}

uint8_t R2FXMessageHandler::toInt(char *arr, uint8_t pos, uint8_t nBytes) {
  String work = String();
  for (uint8_t i = 0; i < nBytes; i++) {
    work += String(arr[pos + i] - '0');
  }
  return work.toInt();
}

void R2FXMessageHandler::messageLoop() {
  if (state != WAIT) {
    byte incommingByte;
    if ((transport == UNKNOWN_TRANSPORT && ble.available() > 0) || transport == BLE_TRANSPORT) {
      incommingByte = ble.read();
      transport = BLE_TRANSPORT;
    } else if ((transport == UNKNOWN_TRANSPORT && Serial.available() > 0) || transport == SERIAL_TRANSPORT) {
      incommingByte = Serial.read();
      transport = SERIAL_TRANSPORT;
    }
  } else if (state == WAIT) {
    const char *response = { '\0' };
    byte exitCode = 0;

    // TODO: needs to return a responcse struct!
    handleMessage(commandBuffer);

    // return exit code and clean up
    returnSerialStatus(exitCode, response);
    clearCommand();
  }
}


