#ifndef UTILITY_H
#define UTILITY_H
// floatToString.h. Tim Hirzel tim@growdown.com March 2008
// If you don't save this as a .h, you will want to remove the default arguments
// uncomment this first line, and swap it for the next.
// (I don't think keyword arguments compile in .pde files)

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Utility {
public:
  char * floatToString(char * outstr, float value, int places, int minwidth = 0, bool rightjustify = false);
};

#endif //UTILITY_H

