/**
 CommandParser.h - A library for retreiving and processesing commands.
  
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

class CommandParser {
  private:
    char cmdIndex = 0; // never greater than 16
    enum CmdState {
      RECEIVING, EMPTY, WAIT
    };
    CmdState state = EMPTY;

  public:
    /**
    * Read from the commandBuffer when the cmdState is in wait.
    */
    char commandBuffer[16] = {0};
    
    /**
    * Processes the serial line and returns true when a command is WAITING
    */
    bool hasCommand();
    
    /**
    * Once a command has been processed, clear it so another can be processed.
    */
    void clearCommand();
    
    /**
    * Utility method to return the state of the command being processd.
    */
    void returnStatus(byte exitCode, const char *msg);
};
#endif // COMMAND_PARSER_H
