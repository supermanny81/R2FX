/**
 CommandParser.h - A library for retreiving and processesing commands.

  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

  BSD license, all text above must be included in any redistribution
**/

#include "CommandParser.h"

// returns true when the command buffer has a command to be processed.
bool CommandParser::hasCommand() {
  if (state == WAIT) {
    return true;
  } else {
    if (Serial.available() > 0) {
      // read the incoming byte:
      char incomingChar = Serial.read();

      if (incomingChar == '[') {
        clearCommand();
        state = RECEIVING;
      } else if (incomingChar == ']' && state == RECEIVING) {
        state = WAIT;
      } else {
        if (cmdIndex == 16) {
          clearCommand();
          returnStatus(1, NULL);
        }
        commandBuffer[cmdIndex] = incomingChar;
        cmdIndex++;
      }
    }
  }
  return false;
}

void CommandParser::clearCommand() {
  memset(commandBuffer, 0, sizeof(commandBuffer));
  cmdIndex = 0;
  state = EMPTY;
}

void CommandParser::returnStatus(byte exitCode, const char *msg) {
  if(msg != '\0') {
    Serial.println(msg);
  }
  if (exitCode == 0) {
    Serial.println(F("OK"));
  }  else if (exitCode == 1) {
    Serial.println(F("ERR: Buffer overflow, command too long."));
  }  else if (exitCode == 2) {
    Serial.println(F("ERR: Unknown command."));
  }
}
