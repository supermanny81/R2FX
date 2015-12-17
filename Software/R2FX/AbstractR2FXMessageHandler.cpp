/**
 AbstractR2FXMessageHandler.cpp - A library for retreiving and processesing commands.

  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

  BSD license, all text above must be included in any redistribution
**/

#include "AbstractR2FXMessageHandler.h"

void AbstractR2FXMessageHandler::processByte(byte incomingByte) {
  // process binary command types here...
  if ((state == EMPTY && incomingByte > 127) || type == BINARY_CMD_TYPE) {
    if (state == EMPTY) {
      clearCommand();
      state = RECEIVING;
      type = BINARY_CMD_TYPE;
    }
    commandBuffer[cmdIndex] = incomingByte;
    cmdIndex++;
  } else {
    // process ascii command types here...
    if (incomingByte == '[') {
      clearCommand();
      type = ASCII_CMD_TYPE;
      state = RECEIVING;
    } else if (incomingByte == ']' && state == RECEIVING) {
      state = WAIT;
    }  else {
      commandBuffer[cmdIndex] = incomingByte;
      cmdIndex++;
    }
  }

  if (cmdIndex == MAX_COMMAND_BUFFER_SIZE) {
    clearCommand();
    returnStatus(1, NULL);
  }
}

void AbstractR2FXMessageHandler::clearCommand() {
  memset(commandBuffer, 0, sizeof(commandBuffer));
  cmdIndex = 0;
  state = EMPTY;
  type = UNKNOWN_CMD_TYPE;
  transport = UNKNOWN_TRANSPORT;
}

void AbstractR2FXMessageHandler::returnStatus(byte exitCode, const char *msg) {
  if (msg != '\0') {
    Serial.println(msg);
  }
  switch (exitCode) {
    case 0: {
        Serial.println(F("OK"));
        break;
      }
    case 1: {
        Serial.println(F("ERR: Buffer overflow, command too long."));
        break;
      }
    case 2: {
        Serial.println(F("ERR: Unknown command."));
        break;
      }
    case 3: {
        Serial.println(F("ERR: Not implemented."));
      }
  }
}

void AbstractR2FXMessageHandler::handleASCIIMessage(char *cmd) {
  Serial.println(cmd);
  const char *response;
  switch (cmd[0]) {
    // Dome Panels
    case 'P': {
        switch (cmd[1]) {
          // Pie Panels
          case 'P': {
              switch (cmd[2]) {
                case 'C': {
                    setDomePpcPos(toInt(cmd, 3, 3), 0);
                    break;
                  }
                case '1': {
                    setDomePp1Pos(toInt(cmd, 3, 3), 0);
                    break;
                  }
                case '2': {
                    setDomePp2Pos(toInt(cmd, 3, 3), 0);
                    break;
                  }
                case '5': {
                    setDomePp5Pos(toInt(cmd, 3, 3), 0);
                    break;
                  }
                case '6': {
                    setDomePp6Pos(toInt(cmd, 3, 3), 0);
                    break;
                  }
              }
              break;
            }
          case '1': {
              setDomeP1Pos(toInt(cmd, 2, 3), 0);
              break;
            }
          case '2': {
              setDomeP2Pos(toInt(cmd, 2, 3), 0);
              break;
            }
          case '3': {
              setDomeP3Pos(toInt(cmd, 2, 3), 0);
              break;
            }
          case '4': {
              setDomeP4Pos(toInt(cmd, 2, 3), 0);
              break;
            }
          case '7': {
              setDomeP7Pos(toInt(cmd, 2, 3), 0);
              break;
            }
          case 'A': {
              setDomeP10Pos(toInt(cmd, 2, 3), 0);
              break;
            }
        }
        break;
      }
    // Body Commands
    case 'C': {
        switch (cmd[1]) {
          case 'B': {
              if (cmd[2] == 'I') {
                setChargeBayEnabled(toInt(cmd, 3, 1));
              } else {
                setBodyChargeBayPosition(toInt(cmd, 2, 3), 0);
              }
              break;
            }
        }
        break;
      }
    case 'D': {
        switch (cmd[1]) {
          case 'P': {
              if (cmd[2] == 'L') {
                setDataPortLogicsEnabled(toInt(cmd, 3, 1));
              } else {
                setBodyDataPortPosition(toInt(cmd, 2, 3), 0);
              }
              break;
            }
        }
        break;
      }
    case 'L': {
        switch (cmd[1]) {
          case 'B': {
              setBodyLowerChargeBayPosition(toInt(cmd, 2, 3), 0);
              break;
            }
        }
        break;
      }
    case 'U': {
        switch (cmd[1]) {
          case 'T': {
              setBodyUATopPosition(toInt(cmd, 2, 3), 0);
              break;
            }
          case 'B': {
              setBodyUABottomPosition(toInt(cmd, 2, 3), 0);
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
              //     char buff[5];
              //   Utility util = Utility();
              // response = util.floatToString(buff, vd->getVCCInPct(), 2, 0);
              break;
            }
          case 'D': {
              //  char buff[5];
              //Utility util = Utility();
              //response = util.floatToString(buff, vd->getVCC(), 2, 0);
              break;
            }
        }
        break;
      }
    default: {
        returnStatus(2, '\0');
      }
  }
}

uint8_t AbstractR2FXMessageHandler::toInt(char *arr, uint8_t pos, uint8_t nBytes) {
  String work = String();
  for (uint8_t i = 0; i < nBytes; i++) {
    work += String(arr[pos + i] - '0');
  }
  return work.toInt();
}

void AbstractR2FXMessageHandler::setDomePpcPos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomePp1Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomePp2Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomePp5Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomePp6Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomeP1Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomeP2Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomeP3Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomeP4Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomeP7Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDomeP10Pos(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setChargeBayEnabled(boolean enabled) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setDataPortLogicsEnabled(boolean enabled) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyUATopPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyUABottomPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyDataPortPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyChargeBayPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyLowerChargeBayPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyFrontRightDoorPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyFrontLeftDoorPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyRearRightDoorPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}

void AbstractR2FXMessageHandler::setBodyRearLeftDoorPosition(byte pos, int duration) {
  returnStatus(3, '\0');
}
