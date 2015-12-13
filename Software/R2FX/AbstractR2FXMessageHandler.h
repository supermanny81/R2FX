/**
 AbstractR2FXMessageHandler.h - A library for retreiving and processesing commands.

  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

  BSD license, all text above must be included in any redistribution
**/

#ifndef Command_Parser_h
#define Command_Parser_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class AbstractR2FXMessageHandler {
  private:
    byte cmdIndex = 0; // never greater than 16

  public:
    enum CmdState {
      RECEIVING, EMPTY, WAIT
    };
    enum CmdType {
      UNKNOWN_CMD_TYPE, ASCII_CMD_TYPE, BINARY_CMD_TYPE
    };
    enum CmdTransport {
      UNKNOWN_TRANSPORT, SERIAL_TRANSPORT, I2C_TRANSPORT, BLE_TRANSPORT
    };
    
    CmdState state = EMPTY;
    CmdType type = UNKNOWN_CMD_TYPE;
    CmdTransport transport = UNKNOWN_TRANSPORT;
    
    /**
    * Read from the commandBuffer when the cmdState is in wait.
    */
    char commandBuffer[16] = {0};

    /**
    * Processes the next byte in the incoming stream.
    */
    void processByte(byte incomingByte);

    /**
    * Once a command has been processed, clear it so another can be processed.
    */
    void clearCommand();

    /**
    * Utility method to return the state of the command being processd.
    */
    void returnSerialStatus(byte exitCode, const char *msg);

    virtual void messageLoop();
};
#endif // Command_Parser_h
