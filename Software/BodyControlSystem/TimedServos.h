#ifndef TimedServos_h
#define TimedServos_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "BodyConfig.h"
#include "elapsedMillis.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"

class TimedServos {

    typedef struct
    {
      int start_pos = 0;
      int end_pos = 0;
      int time_allotted = 0;
      elapsedMillis sinceLastCmd;
      int srv_min;
      int srv_max;
      boolean isInversed = false;
    }  TimedServo;

    TimedServo bodyServo[BODY_PWM_SHIELD_CHANNELS];

  private:
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(BODY_PWM_SHIELD_ADDRESS);

    void initializeBodyServoConfig();

    void setServoPosition(int SRV_NUM, int SRV_POS, int SRV_MIN, int SRV_MAX);

  public:
    TimedServos();

    /**
     * Sets the targeted servo position and the amount of time alloted to reach the position.
     */
    void setServoPosition(int channel, int srv_pos, int time_alloted);
    void setUATop(int degree);
    void setUABottom(int degree);
    void processMovements();
    void sweep();
};

#endif // TimedServos.h
