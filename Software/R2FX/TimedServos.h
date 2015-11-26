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
      uint8_t start_pos = 0;
      uint8_t end_pos = 0;
      uint8_t curr_pos = 0;
      uint16_t time_allotted = 0;
      unsigned long millisAtCommand = 0;
      uint16_t srv_min;
      uint16_t srv_max;
      boolean isInversed = false;
      boolean isDisabled = false;
    }  TimedServo;

    typedef struct 
    {
      TimedServo channels[16];
      Adafruit_PWMServoDriver pwm;
    } PWMBoard;

    PWMBoard servoBoards[2];
        
  private:
    void setServoPulse(Adafruit_PWMServoDriver pwm, uint8_t srv_num, uint8_t srv_pos, uint16_t srv_min, uint16_t srv_max);
    void disableChannel(Adafruit_PWMServoDriver pwm, uint8_t srv_num);
    void initializeBodyServoConfig();
    void initializeDomeConfig();

  public:
    TimedServos();

    /**
     * Sets the targeted servo position and the amount of time alloted to reach the position.
     */
    void setServoPosition(uint8_t board, uint8_t channel, uint8_t srv_pos, uint16_t time_alloted);
    void setUATop(int degree);
    void setUABottom(int degree);
    void processMovements();
    void sweep();
    void setup();
};

#endif // TimedServos.h
