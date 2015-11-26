#include "BodyConfig.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "TimedServos.h"

TimedServos::TimedServos() {}

void TimedServos::setup() {
  initializeBodyServoConfig();
  initializeDomeConfig();
}

void TimedServos::initializeBodyServoConfig() {
  // Configure body system
  servoBoards[0].pwm.begin();
  servoBoards[0].pwm.setPWMFreq(BODY_PWM_SHIELD_SERVO_FREQ);

  servoBoards[0].channels[SV_UA_TOP].isInversed = SV_UA_IS_INVERSED;
  servoBoards[0].channels[SV_UA_TOP].srv_min = SV_UA_TOP_MIN;
  servoBoards[0].channels[SV_UA_TOP].srv_max = SV_UA_TOP_MAX;

  servoBoards[0].channels[SV_UA_BOTTOM].isInversed = SV_UA_BOTTOM_IS_INVERSED;
  servoBoards[0].channels[SV_UA_BOTTOM].srv_min = SV_UA_BOTTOM_MIN;
  servoBoards[0].channels[SV_UA_BOTTOM].srv_max = SV_UA_BOTTOM_MAX;

  servoBoards[0].channels[SV_CBI].isInversed = SV_CBI_IS_INVERSED;
  servoBoards[0].channels[SV_CBI].srv_min = SV_CBI_MIN;
  servoBoards[0].channels[SV_CBI].srv_max = SV_CBI_MAX;

  servoBoards[0].channels[SV_LOWER_CBI].isInversed = SV_LOWER_CBI_IS_INVERSED;
  servoBoards[0].channels[SV_LOWER_CBI].srv_min = SV_LOWER_CBI_MIN;
  servoBoards[0].channels[SV_LOWER_CBI].srv_max = SV_LOWER_CBI_MAX;

  servoBoards[0].channels[SV_DPI].isInversed = SV_DPI_IS_INVERSED;
  servoBoards[0].channels[SV_DPI].srv_min = SV_DPI_MIN;
  servoBoards[0].channels[SV_DPI].srv_max = SV_DPI_MAX;

  servoBoards[0].channels[SV_FL].isInversed = SV_FL_IS_INVERSED;
  servoBoards[0].channels[SV_FL].srv_min = SV_FL_MIN;
  servoBoards[0].channels[SV_FL].srv_max = SV_FL_MAX;

  servoBoards[0].channels[SV_FR].isInversed = SV_FR_IS_INVERSED;
  servoBoards[0].channels[SV_FR].srv_min = SV_FR_MIN;
  servoBoards[0].channels[SV_FR].srv_max = SV_FR_MAX;

  servoBoards[0].channels[SV_RL].isInversed = SV_RL_IS_INVERSED;
  servoBoards[0].channels[SV_RL].srv_min = SV_RL_MIN;
  servoBoards[0].channels[SV_RL].srv_max = SV_RL_MAX;

  servoBoards[0].channels[SV_RR].isInversed = SV_RR_IS_INVERSED;
  servoBoards[0].channels[SV_RR].srv_min = SV_RR_MIN;
  servoBoards[0].channels[SV_RR].srv_max = SV_RR_MAX;
}

void TimedServos::initializeDomeConfig() {
  // Configure dome system
  servoBoards[1].pwm.begin();
  servoBoards[1].pwm.setPWMFreq(DOME_PWM_SHIELD_SERVO_FREQ);

  servoBoards[1].channels[SV_PPC].isInversed = SV_PPC_IS_INVERSED;
  servoBoards[1].channels[SV_PPC].srv_min = SV_PPC_MIN;
  servoBoards[1].channels[SV_PPC].srv_max = SV_PPC_MAX;

  servoBoards[1].channels[SV_PP1].isInversed = SV_PP1_IS_INVERSED;
  servoBoards[1].channels[SV_PP1].srv_min = SV_PP1_MIN;
  servoBoards[1].channels[SV_PP1].srv_max = SV_PP1_MAX;


  servoBoards[1].channels[SV_PP2].isInversed = SV_PP2_IS_INVERSED;
  servoBoards[1].channels[SV_PP2].srv_min = SV_PP2_MIN;
  servoBoards[1].channels[SV_PP2].srv_max = SV_PP2_MAX;

  servoBoards[1].channels[SV_PP5].isInversed = SV_PP5_IS_INVERSED;
  servoBoards[1].channels[SV_PP5].srv_min = SV_PP5_MIN;
  servoBoards[1].channels[SV_PP5].srv_max = SV_PP5_MAX;

  servoBoards[1].channels[SV_PP6].isInversed = SV_PP6_IS_INVERSED;
  servoBoards[1].channels[SV_PP6].srv_min = SV_PP6_MIN;
  servoBoards[1].channels[SV_PP6].srv_max = SV_PP6_MAX;

  servoBoards[1].channels[SV_P1].isInversed = SV_P1_IS_INVERSED;
  servoBoards[1].channels[SV_P1].srv_min = SV_P1_MIN;
  servoBoards[1].channels[SV_P1].srv_max = SV_P1_MAX;

  servoBoards[1].channels[SV_P2].isInversed = SV_P2_IS_INVERSED;
  servoBoards[1].channels[SV_P2].srv_min = SV_P2_MIN;
  servoBoards[1].channels[SV_P2].srv_max = SV_P2_MAX;

  servoBoards[1].channels[SV_P3].isInversed = SV_P3_IS_INVERSED;
  servoBoards[1].channels[SV_P3].srv_min = SV_P3_MIN;
  servoBoards[1].channels[SV_P3].srv_max = SV_P3_MAX;

  servoBoards[1].channels[SV_P4].isInversed = SV_P4_IS_INVERSED;
  servoBoards[1].channels[SV_P4].srv_min = SV_P4_MIN;
  servoBoards[1].channels[SV_P4].srv_max = SV_P4_MAX;

  servoBoards[1].channels[SV_P7].isInversed = SV_P7_IS_INVERSED;
  servoBoards[1].channels[SV_P7].srv_min = SV_P7_MIN;
  servoBoards[1].channels[SV_P7].srv_max = SV_P7_MAX;

  servoBoards[1].channels[SV_PA].isInversed = SV_PA_IS_INVERSED;
  servoBoards[1].channels[SV_PA].srv_min = SV_PA_MIN;
  servoBoards[1].channels[SV_PA].srv_max = SV_PA_MAX;
}

void TimedServos::setServoPosition(uint8_t board, uint8_t channel, uint8_t srv_pos, uint16_t time_allotted) {
  srv_pos = srv_pos > 180 ? 180 : srv_pos;
  // change target servo position for inversed servos
  if (servoBoards[board].channels[channel].isInversed)
    srv_pos = map( srv_pos, 0, 180, 180, 0);

  // makes sure we don't attempt to make the servos travel faster than possible
  uint16_t min_travel_time = abs(servoBoards[board].channels[channel].curr_pos - srv_pos) * PWM_MAX_TRAVEL_PER_MILLI;
  time_allotted = (min_travel_time > time_allotted) ? min_travel_time : time_allotted;
  // set the position and time to reach it
  servoBoards[board].channels[channel].start_pos = servoBoards[board].channels[channel].curr_pos;
  servoBoards[board].channels[channel].end_pos = srv_pos;
  servoBoards[board].channels[channel].time_allotted = time_allotted;
  servoBoards[board].channels[channel].millisAtCommand = millis();
  servoBoards[board].channels[channel].isDisabled = false;
}

void TimedServos::processMovements() {
  for (uint8_t board = 0; board < 2; board++) {
    for (uint8_t channel = 0; channel < 16; channel++) {
      unsigned long timeElapsed = (millis() - servoBoards[board].channels[channel].millisAtCommand);
      if (servoBoards[board].channels[channel].curr_pos != servoBoards[board].channels[channel].end_pos) {
        if (servoBoards[board].channels[channel].end_pos > servoBoards[board].channels[channel].start_pos) {
          uint8_t degree = map(timeElapsed, 0, servoBoards[board].channels[channel].time_allotted, servoBoards[board].channels[channel].start_pos, servoBoards[board].channels[channel].end_pos);
          servoBoards[board].channels[channel].curr_pos = (degree > 180) ? 180 : degree;
        } else {
          uint8_t degree = map(timeElapsed, 0, servoBoards[board].channels[channel].time_allotted, servoBoards[board].channels[channel].start_pos, servoBoards[board].channels[channel].end_pos);
          servoBoards[board].channels[channel].curr_pos =  (degree  > 180) ? 0 : degree;
        }
        setServoPulse(servoBoards[board].pwm, channel, servoBoards[board].channels[channel].curr_pos, servoBoards[board].channels[channel].srv_min, servoBoards[board].channels[channel].srv_max);
      } else if (timeElapsed > (servoBoards[board].channels[channel].time_allotted + 500)
                 && !servoBoards[board].channels[channel].isDisabled
                 && servoBoards[board].channels[channel].curr_pos == servoBoards[board].channels[channel].end_pos) {
        disableChannel(servoBoards[board].pwm, channel);
        servoBoards[board].channels[channel].isDisabled = true;
      }
    }
  }
}


void TimedServos::setServoPulse(Adafruit_PWMServoDriver pwm, uint8_t srv_num, uint8_t srv_pos, uint16_t srv_min, uint16_t srv_max) {
  if (srv_pos > 180) {
    srv_pos = 180;
  }
  uint16_t pulselength = map(srv_pos, 0, 180, srv_min, srv_max);
  pwm.setPWM(srv_num, 0, pulselength);
}

void TimedServos::disableChannel(Adafruit_PWMServoDriver pwm, uint8_t srv_num) {
  pwm.setPWM(srv_num, 0, 0);
}
