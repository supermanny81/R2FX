/**
  TimedServos.h - A library for managing timed servo movements on PWM boards.

  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

  BSD license, all text above must be included in any redistribution
**/
#include "R2FXConfig.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "TimedServos.h"

TimedServos::TimedServos() {}

TimedServos* TimedServos::getInstance() {
  static TimedServos ts;
  return &ts;
}

void TimedServos::setup() {
  initializeBodyServoConfig();
  initializeDomeConfig();
}

void TimedServos::initializeBodyServoConfig() {
  // Configure body system
  servoBoards[0].pwm.begin();
  servoBoards[0].pwm.setPWMFreq(BODY_PWM_SHIELD_SERVO_FREQ);

  servoBoards[0].channels[SV_UA_TOP].isInversed = SV_UA_IS_INVERSED;
  servoBoards[0].channels[SV_UA_TOP].srvMin = SV_UA_TOP_MIN;
  servoBoards[0].channels[SV_UA_TOP].srvMax = SV_UA_TOP_MAX;

  servoBoards[0].channels[SV_UA_BOTTOM].isInversed = SV_UA_BOTTOM_IS_INVERSED;
  servoBoards[0].channels[SV_UA_BOTTOM].srvMin = SV_UA_BOTTOM_MIN;
  servoBoards[0].channels[SV_UA_BOTTOM].srvMax = SV_UA_BOTTOM_MAX;

  servoBoards[0].channels[SV_CBI].isInversed = SV_CBI_IS_INVERSED;
  servoBoards[0].channels[SV_CBI].srvMin = SV_CBI_MIN;
  servoBoards[0].channels[SV_CBI].srvMax = SV_CBI_MAX;

  servoBoards[0].channels[SV_LOWER_CBI].isInversed = SV_LOWER_CBI_IS_INVERSED;
  servoBoards[0].channels[SV_LOWER_CBI].srvMin = SV_LOWER_CBI_MIN;
  servoBoards[0].channels[SV_LOWER_CBI].srvMax = SV_LOWER_CBI_MAX;

  servoBoards[0].channels[SV_DPI].isInversed = SV_DPI_IS_INVERSED;
  servoBoards[0].channels[SV_DPI].srvMin = SV_DPI_MIN;
  servoBoards[0].channels[SV_DPI].srvMax = SV_DPI_MAX;

  servoBoards[0].channels[SV_FL].isInversed = SV_FL_IS_INVERSED;
  servoBoards[0].channels[SV_FL].srvMin = SV_FL_MIN;
  servoBoards[0].channels[SV_FL].srvMax = SV_FL_MAX;

  servoBoards[0].channels[SV_FR].isInversed = SV_FR_IS_INVERSED;
  servoBoards[0].channels[SV_FR].srvMin = SV_FR_MIN;
  servoBoards[0].channels[SV_FR].srvMax = SV_FR_MAX;

  servoBoards[0].channels[SV_RL].isInversed = SV_RL_IS_INVERSED;
  servoBoards[0].channels[SV_RL].srvMin = SV_RL_MIN;
  servoBoards[0].channels[SV_RL].srvMax = SV_RL_MAX;

  servoBoards[0].channels[SV_RR].isInversed = SV_RR_IS_INVERSED;
  servoBoards[0].channels[SV_RR].srvMin = SV_RR_MIN;
  servoBoards[0].channels[SV_RR].srvMax = SV_RR_MAX;
}

void TimedServos::initializeDomeConfig() {
  // Configure dome system
  // Upper panels
  servoBoards[1].pwm.begin();
  servoBoards[1].pwm.setPWMFreq(DOME_PWM_SHIELD_SERVO_FREQ);

  servoBoards[1].channels[SV_PPC].isInversed = SV_PPC_IS_INVERSED;
  servoBoards[1].channels[SV_PPC].srvMin = SV_PPC_MIN;
  servoBoards[1].channels[SV_PPC].srvMax = SV_PPC_MAX;

  servoBoards[1].channels[SV_PP1].isInversed = SV_PP1_IS_INVERSED;
  servoBoards[1].channels[SV_PP1].srvMin = SV_PP1_MIN;
  servoBoards[1].channels[SV_PP1].srvMax = SV_PP1_MAX;

  servoBoards[1].channels[SV_PP2].isInversed = SV_PP2_IS_INVERSED;
  servoBoards[1].channels[SV_PP2].srvMin = SV_PP2_MIN;
  servoBoards[1].channels[SV_PP2].srvMax = SV_PP2_MAX;

  servoBoards[1].channels[SV_PP5].isInversed = SV_PP5_IS_INVERSED;
  servoBoards[1].channels[SV_PP5].srvMin = SV_PP5_MIN;
  servoBoards[1].channels[SV_PP5].srvMax = SV_PP5_MAX;

  servoBoards[1].channels[SV_PP6].isInversed = SV_PP6_IS_INVERSED;
  servoBoards[1].channels[SV_PP6].srvMin = SV_PP6_MIN;
  servoBoards[1].channels[SV_PP6].srvMax = SV_PP6_MAX;

  // Lower panels
  servoBoards[1].channels[SV_P1].isInversed = SV_P1_IS_INVERSED;
  servoBoards[1].channels[SV_P1].srvMin = SV_P1_MIN;
  servoBoards[1].channels[SV_P1].srvMax = SV_P1_MAX;

  servoBoards[1].channels[SV_P2].isInversed = SV_P2_IS_INVERSED;
  servoBoards[1].channels[SV_P2].srvMin = SV_P2_MIN;
  servoBoards[1].channels[SV_P2].srvMax = SV_P2_MAX;

  servoBoards[1].channels[SV_P3].isInversed = SV_P3_IS_INVERSED;
  servoBoards[1].channels[SV_P3].srvMin = SV_P3_MIN;
  servoBoards[1].channels[SV_P3].srvMax = SV_P3_MAX;

  servoBoards[1].channels[SV_P4].isInversed = SV_P4_IS_INVERSED;
  servoBoards[1].channels[SV_P4].srvMin = SV_P4_MIN;
  servoBoards[1].channels[SV_P4].srvMax = SV_P4_MAX;

  servoBoards[1].channels[SV_P7].isInversed = SV_P7_IS_INVERSED;
  servoBoards[1].channels[SV_P7].srvMin = SV_P7_MIN;
  servoBoards[1].channels[SV_P7].srvMax = SV_P7_MAX;

  servoBoards[1].channels[SV_PA].isInversed = SV_PA_IS_INVERSED;
  servoBoards[1].channels[SV_PA].srvMin = SV_PA_MIN;
  servoBoards[1].channels[SV_PA].srvMax = SV_PA_MAX;
}

void TimedServos::setServoPosition(uint8_t board, uint8_t channel, uint8_t srvPos, uint16_t timeAllotted) {
  srvPos = srvPos > 127 ? 127 : srvPos;
  // change target servo position for inversed servos
  if (servoBoards[board].channels[channel].isInversed)
    srvPos = map( srvPos, 0, 127, 127, 0);

  // makes sure we don't attempt to make the servos travel faster than possible
  uint16_t min_travel_time = abs(servoBoards[board].channels[channel].currPos - srvPos) * PWM_MAX_TRAVEL_PER_MILLI;
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
