
#include "R2FXMessageHandler.h"

void R2FXMessageHandler::loop() {
  if (state != WAIT) {
    if ((transport == UNKNOWN_TRANSPORT || transport == BLE_TRANSPORT) && ble.available() > 0) {
      processByte(ble.read());
      transport = BLE_TRANSPORT;
    } else if ((transport == UNKNOWN_TRANSPORT || transport == SERIAL_TRANSPORT) && Serial.available() > 0) {
      processByte(Serial.read());
      transport = SERIAL_TRANSPORT;
    }

  } else if (state == WAIT) {
    const char *response = { '\0' };
    byte exitCode = 0;

    // TODO: 
    handleASCIIMessage((char*) commandBuffer);
    clearCommand();
  }
  //Serial.println(freeMemory());
}

void R2FXMessageHandler::setDomePpcPos(byte pos, int duration) {
  ts->setServoPosition(1, SV_PPC, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomePp1Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_PP1, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomePp2Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_PP2, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomePp5Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_PP5, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomePp6Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_PP6, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomeP1Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_P1, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomeP2Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_P2, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomeP3Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_P3, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomeP4Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_P4, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomeP7Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_P7, pos, duration);
  returnStatus(0, '\0');
}

void R2FXMessageHandler::setDomeP10Pos(byte pos, int duration) {
  ts->setServoPosition(1, SV_PA, pos, duration);
  returnStatus(0, '\0');
}

/**
 * TODO: Saving for later...
 * 
 * 
void AbstractR2FXMessageHandler::handleASCIIMessage(char *cmd) {
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
**/
