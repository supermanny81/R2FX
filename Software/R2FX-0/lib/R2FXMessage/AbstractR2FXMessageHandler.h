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

#define MAX_COMMAND_BUFFER_SIZE 16

#include "Utility.h"

class AbstractR2FXMessageHandler {
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
    byte commandBuffer[MAX_COMMAND_BUFFER_SIZE] = {0};

    /**
    * Processes the next byte in the incoming stream.
    */
    void processByte(byte incomingByte);

    /**
    * Once a command has been processed, clear the state of the message handler so another can be processed.
    */
    void clearCommand();

    /**
    * Utility method to return the state of the command being processd via the serial interface.
    */
    void returnStatus(byte exitCode, const char *msg);

    uint8_t toInt(char *arr, uint8_t pos, uint8_t nBytes);

    void handleASCIIMessage(char *cmd);

    void handleBinaryMessage(byte *cmd);
    
    /**
     *  This method needs an implementation when subclassed in other R2FX enabled systems.
     */
    virtual void loop() = 0;

  private:
    byte cmdIndex = 0; // never greater than MAX_COMMAND_BUFFER_SIZE

    /***
     **  Override these methods with your default implementations for the varios systems
     **/

    /**
     * Dome Systems
     */
    virtual void setDomePpcPos(byte pos, int duration); // center pie panel
    virtual void setDomePp1Pos(byte pos, int duration); // pie panel 1
    virtual void setDomePp2Pos(byte pos, int duration); // pie panel 2
    virtual void setDomePp5Pos(byte pos, int duration); // pie panel 5
    virtual void setDomePp6Pos(byte pos, int duration); // pie panel 6

    virtual void setDomeP1Pos(byte pos, int duration); // panel 1
    virtual void setDomeP2Pos(byte pos, int duration); // panel 2
    virtual void setDomeP3Pos(byte pos, int duration); // panel 3
    virtual void setDomeP4Pos(byte pos, int duration); // panel 4
    virtual void setDomeP7Pos(byte pos, int duration); // panel 7
    virtual void setDomeP10Pos(byte pos, int duration); // panel 10

    /**
     * Charge Bay and Data Port Logics
     */
    virtual void setChargeBayEnabled(boolean enabled);
    virtual void setDataPortLogicsEnabled(boolean enabled);

    /**
     * Override these methods with your default implementation for setting positions on the body systems
     */
    virtual void setBodyUATopPosition(byte pos, int duration);
    virtual void setBodyUABottomPosition(byte pos, int duration);

    virtual void setBodyDataPortPosition(byte pos, int duration);
    virtual void setBodyChargeBayPosition(byte pos, int duration);
    virtual void setBodyLowerChargeBayPosition(byte pos, int duration);

    virtual void setBodyFrontRightDoorPosition(byte pos, int duration);
    virtual void setBodyFrontLeftDoorPosition(byte pos, int duration);
    virtual void setBodyRearRightDoorPosition(byte pos, int duration);
    virtual void setBodyRearLeftDoorPosition(byte pos, int duration);

};
#endif // Command_Parser_h
