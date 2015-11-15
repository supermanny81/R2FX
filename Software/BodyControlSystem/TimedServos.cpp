#include "BodyConfig.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "TimedServos.h"

TimedServos::TimedServos() {
  pwm.begin();
  pwm.setPWMFreq(BODY_PWM_SHIELD_SERVO_FREQ);  // This is the maximum PWM frequency
  TWBR = 12; // upgrade to 400KHz!
  initializeBodyServoConfig();
}

void TimedServos::initializeBodyServoConfig() {
  bodyServo[SV_UA_TOP].srv_min = SV_UA_TOP_MIN;
  bodyServo[SV_UA_TOP].srv_max = SV_UA_TOP_MAX;

  bodyServo[SV_UA_BOTTOM].srv_min = SV_UA_BOTTOM_MIN;
  bodyServo[SV_UA_BOTTOM].srv_max = SV_UA_BOTTOM_MAX;

  bodyServo[SV_CBI].srv_min = SV_CBI_MIN;
  bodyServo[SV_CBI].srv_max = SV_CBI_MAX;

  bodyServo[SV_LOWER_CBI].srv_min = SV_LOWER_CBI_MIN;
  bodyServo[SV_LOWER_CBI].srv_max = SV_LOWER_CBI_MAX;

  bodyServo[SV_DPI].srv_min = SV_DPI_MIN;
  bodyServo[SV_DPI].srv_max = SV_DPI_MAX;

  bodyServo[SV_FL].srv_min = SV_FL_MIN;
  bodyServo[SV_FL].srv_max = SV_FL_MAX;

  bodyServo[SV_FR].srv_min = SV_FR_MIN;
  bodyServo[SV_FR].srv_max = SV_FR_MAX;

  bodyServo[SV_RL].srv_min = SV_RL_MIN;
  bodyServo[SV_RL].srv_max = SV_RL_MAX;

  bodyServo[SV_RR].srv_min = SV_RR_MIN;
  bodyServo[SV_RR].srv_max = SV_RR_MAX;
}

void TimedServos::setServoPosition(int channel, int srv_pos, int time_alloted) {
  // makes sure we don't attempt to make the servos travel faster than possible
  int min_travel_time = abs(bodyServo[channel].start_pos - srv_pos) * BODY_PWM_MAX_TRAVEL_PER_MILLI;
  time_alloted = (min_travel_time > time_alloted) ? min_travel_time : time_alloted;
  
  bodyServo[channel].end_pos = bodyServo[channel].start_pos;
  bodyServo[channel].start_pos = srv_pos;
  bodyServo[channel].time_allotted = time_alloted;
}

void TimedServos::processMovements() {


}








void TimedServos::setServoPosition(int srv_num, int srv_pos, int srv_min, int srv_max) {
  if (srv_pos > 180) {
    srv_pos = 180;
  }
  uint16_t pulselength = map(srv_pos, 0, 180, srv_min, srv_max);
  pwm.setPWM(srv_num, 0, pulselength);
}

void TimedServos::setUATop(int degree) {
  setServoPosition(SV_UA_TOP, degree, SV_UA_TOP_MIN, SV_UA_TOP_MAX);
}

void TimedServos::setUABottom(int degree) {
  setServoPosition(SV_UA_BOTTOM, degree, SV_UA_BOTTOM_MIN, SV_UA_BOTTOM_MAX);
}


void TimedServos::sweep() {
  for (int i = 0; i <= 180; i += 20) {
    setServoPosition(SV_UA_TOP, i, SV_UA_TOP_MIN, SV_UA_TOP_MAX);
    delay(40);
  }
  pwm.setPWM(SV_UA_TOP, 0, 0);
  delay(500);

  for (int i = 180; i >= 0; i -= 20) {
    setServoPosition(SV_UA_TOP, i, SV_UA_TOP_MIN, SV_UA_TOP_MAX);
    delay(40);
  }
  pwm.setPWM(SV_UA_TOP, 0, 0);
}

