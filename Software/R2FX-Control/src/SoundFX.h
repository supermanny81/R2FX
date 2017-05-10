#ifndef SOUNDS_H_
#define SOUNDS_H_
//************************* Sound Settings *****************************//
#define WAVBAUDRATE 57600

// 10 = max, -70 min
#define DEFAULT_VOLUME_MIN -70
#define DEFAULT_VOLUME_MAX 10
#define DEFAULT_VOLUME -20

#include <Stream.h>
#include "WavTrigger2.h"

class SoundFX {
    private:
      WavTrigger2 wTrig;
      char vol = DEFAULT_VOLUME;
      bool isBgMusicPlaying = false;
      SoundFX();
      SoundFX(SoundFX const&); // copy disabled
      void operator=(SoundFX const&); // assigment disabled
      void setVol(int vol);

  public:
    static SoundFX* getInstance();
    void setup(Stream* stream);
    void volUp();
    void volDown();
    void play(int track);
    void printWTrigInfo();

};

#endif //SOUNDS_H
