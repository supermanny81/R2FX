/**
 R2FS.h - Used for the storage and playback of sequences stored by the R2FX system.

  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

  BSD license, all text above must be included in any redistribution
**/
#ifndef R2FS_h
#define R2FS_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Adafruit_FRAM_I2C.h>

class R2FS {

  private:
    Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();
    uint16_t          framAddr = 0;
  public:
    void testFRAM();

};
#endif // R2FS_h
