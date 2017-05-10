/**
  TimedServos.h - A library for managing timed servo movements on PWM boards.

  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

  BSD license, all text above must be included in any redistribution
**/
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "TimedServos.h"

TimedServos::TimedServos() {}

TimedServos* TimedServos::getInstance() {
  static TimedServos ts;
  return &ts;
}

void TimedServos::setup() {
  servoBoards[0].pwm = Adafruit_PWMServoDriver(0x40);
  servoBoards[0].pwm.begin();
  servoBoards[0].pwm.setPWMFreq(60);
  servoBoards[1].pwm = Adafruit_PWMServoDriver(0x41);
  servoBoards[1].pwm.begin();
  servoBoards[1].pwm.setPWMFreq(60);
}

void TimedServos::setServoPosition(uint8_t board, uint8_t channel, uint8_t srvPos, uint16_t timeAllotted) {
  srvPos = srvPos > 127 ? 127 : srvPos;
  // change target servo position for inversed servos
  if (servoBoards[board].channels[channel].isInversed)
    srvPos = map( srvPos, 0, 127, 127, 0);

  // makes sure we don't attempt to make the servos travel faster than possible
  uint16_t min_travel_time = abs(servoBoards[board].channels[channel].currPos - srvPos) / PWM_MAX_TRAVEL_PER_MILLI;
  timeAllotted = (min_travel_time > timeAllotted) ? min_travel_time : timeAllotted;
  // set the position and time to reach it
  servoBoards[board].channels[channel].startPos = servoBoards[board].channels[channel].currPos;
  servoBoards[board].channels[channel].endPos = srvPos;
  servoBoards[board].channels[channel].timeAllotted = timeAllotted;
  servoBoards[board].channels[channel].millisAtCommand = millis();
  servoBoards[board].channels[channel].isDisabled = false;
}

void TimedServos::setServoPulse(Adafruit_PWMServoDriver pwm, uint8_t srvNum, uint8_t srvPos, uint16_t srvMin, uint16_t srvMax) {
  if (srvPos > 127) {
    srvPos = 127;
  }
  uint16_t pulselength = map(srvPos, 0, 127, srvMin, srvMax);
  pwm.setPWM(srvNum, 0, pulselength);
}

void TimedServos::disableChannel(Adafruit_PWMServoDriver pwm, uint8_t srvNum) {
  pwm.setPWM(srvNum, 0, 0);
}

void TimedServos::loop() {
  for (uint8_t board = 0; board < 2; board++) {
    for (uint8_t channel = 0; channel < 16; channel++) {
      unsigned long timeElapsed = (millis() - servoBoards[board].channels[channel].millisAtCommand);
      if (servoBoards[board].channels[channel].currPos != servoBoards[board].channels[channel].endPos) {

        if (servoBoards[board].channels[channel].endPos > servoBoards[board].channels[channel].startPos) {
          uint8_t degree = map(timeElapsed, 0, servoBoards[board].channels[channel].timeAllotted, servoBoards[board].channels[channel].startPos, servoBoards[board].channels[channel].endPos);
          servoBoards[board].channels[channel].currPos = (degree > 127) ? 127 : degree;
        } else {
          uint8_t degree = map(timeElapsed, 0, servoBoards[board].channels[channel].timeAllotted, servoBoards[board].channels[channel].startPos, servoBoards[board].channels[channel].endPos);
          servoBoards[board].channels[channel].currPos =  (degree  > 127) ? 0 : degree;
        }
        setServoPulse(servoBoards[board].pwm, channel, servoBoards[board].channels[channel].currPos, servoBoards[board].channels[channel].srvMin, servoBoards[board].channels[channel].srvMax);
      } else if (timeElapsed > (servoBoards[board].channels[channel].timeAllotted + 500)
                 && !servoBoards[board].channels[channel].isDisabled
                 && servoBoards[board].channels[channel].currPos == servoBoards[board].channels[channel].endPos) {
        disableChannel(servoBoards[board].pwm, channel);
        servoBoards[board].channels[channel].isDisabled = true;
      }
    }
  }
}
