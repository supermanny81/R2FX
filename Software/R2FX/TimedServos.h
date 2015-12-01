/**
  TimedServos.h - A library for managing timed servo movements on PWM boards.

  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

  BSD license, all text above must be included in any redistribution
**/
#ifndef TimedServos_h
#define TimedServos_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "R2FXConfig.h"
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

    /**
     * This method needs to be called in a loop and will iterate through any sets of movements that are currently 
     * in action or disable a servo once it has reached it position for the defined period of time.
     */
    void processMovements();

    /**
     * Configures the TimedServo classes, boards and thier assignments.  This method must be called 
     * once before any servo movement is attempted.
     */
    void setup();
};

#endif // TimedServos.h
