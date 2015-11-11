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
}

void TimedServos::setServoPosition(int srv_num, int srv_pos, int srv_min, int srv_max) {
  if (srv_pos > 180) {
    srv_pos = 180;
  }
  uint16_t pulselength = map(srv_pos, 0, 180, srv_min, srv_max);
  pwm.setPWM(srv_num, 0, pulselength);

  Serial.println(pulselength);
}

void TimedServos::setUATop(int degree) {
  setServoPosition(SV_UA_TOP, degree, SV_UA_TOP_MIN, SV_UA_TOP_MAX);
}

void TimedServos::setUABottom(int degree) {
  setServoPosition(SV_UA_BOTTOM, degree, SV_UA_BOTTOM_MIN, SV_UA_BOTTOM_MAX);
}

void TimedServos::processMovements() {


}

void TimedServos::sweep() {
  for (int i = 0; i <= 180; i += 20) {
    setServoPosition(SV_UA_TOP, i, SV_UA_TOP_MIN, SV_UA_TOP_MAX);
    delay(100);
  }

  for (int i = 180; i >= 0; i -= 20) {
    setServoPosition(SV_UA_TOP, i, SV_UA_TOP_MIN, SV_UA_TOP_MAX);
    delay(90);
  }
  pwm.setPWM(SV_UA_TOP, 0, 0);
}

