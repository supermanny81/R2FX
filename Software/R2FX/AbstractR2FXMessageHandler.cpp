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
  } else {
    // process ascii command types here...
    if (incomingByte == '[') {
      clearCommand();
      type = ASCII_CMD_TYPE;
      state = RECEIVING;
    } else if (incomingByte == ']' && state == RECEIVING) {
      state = WAIT;
    }
  }
  commandBuffer[cmdIndex] = incomingByte;
  cmdIndex++;
  
  if (cmdIndex == 16) {
    clearCommand();
    returnSerialStatus(1, NULL);
  }
}

void AbstractR2FXMessageHandler::clearCommand() {
  memset(commandBuffer, 0, sizeof(commandBuffer));
  cmdIndex = 0;
  state = EMPTY;
  type = UNKNOWN_CMD_TYPE;
  transport = UNKNOWN_TRANSPORT;
}

void AbstractR2FXMessageHandler::returnSerialStatus(byte exitCode, const char *msg) {
  if (msg != '\0') {
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
