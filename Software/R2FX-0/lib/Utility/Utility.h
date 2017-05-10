#ifndef UTILITY_H
#define UTILITY_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Utility {
public:
  /** 
   *  Returns a character based represenation of a float
   *  
   *  Credit for this function goes to Tim Hirzel tim@grodown.com March 2008
   */
  static char * floatToString(char * outstr, float value, int places, int minwidth = 0, bool rightjustify = false);

  /**
   * Converts an array or part of an array from characters to an integer
   */
  static uint8_t toInt(char *arr, uint8_t pos, uint8_t nBytes);
};

#endif //UTILITY_H

