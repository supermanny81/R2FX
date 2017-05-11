#ifndef UA_H_
#define UA_H_

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <ArduinoLog.h>

#include "TimedServos.h"

#define SV_UA_BOARD 1
#define SV_UA_TOP 0
#define SV_UA_IS_INVERSED true
#define SV_UA_TOP_MIN 280
#define SV_UA_TOP_MAX 510

#define SV_UA_BOTTOM 1
#define SV_UA_BOTTOM_IS_INVERSED true
#define SV_UA_BOTTOM_MIN 290
#define SV_UA_BOTTOM_MAX 540

class UA {

    boolean isTopOpen = true;
    boolean isBottomOpen = true;

  private:
    TimedServos* ts = TimedServos::getInstance();
    UA();
    UA(UA const&); // copy disabled
    void operator=(UA const&); // assigment disabled

  public:
    static UA* getInstance();
    void setup();
    void setUpperArmPosition(byte pos, int timeAllotted = 0);
    void setLowerArmPosition(byte pos, int timeAllotted = 0);

    void toggleUpper();
    void toggleLower();

    void openAll();
    void closeAll();
};
#endif //UA_H_
