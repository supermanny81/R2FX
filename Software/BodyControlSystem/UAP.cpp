#include "BodyConfig.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "UAP.h"

UAP::UAP() {
  pwm= Adafruit_PWMServoDriver(PWM_SHIELD_ADDRESS);
  pwm.begin();
  pwm.setPWMFreq(60);  // This is the maximum PWM frequency
  TWBR = 12; // upgrade to 400KHz! 
}

void UAP::setServoPosition(int srv_num, int srv_pos, int srv_min, int srv_max) {
    if (srv_pos > 180) {
     srv_pos = 180;
   }
   int pulselen = map(srv_pos, 0, 180, srv_min, srv_max); 
   pwm.setPWM(srv_num, 0, pulselen);
}

void UAP::setUATop(int degree) {
  setServoPosition(SV_UA_TOP, degree, SV_UA_TOP_MIN, SV_UA_TOP_MAX);
}

void UAP::setUABottom(int degree) {
  setServoPosition(SV_UA_BOTTOM, degree, SV_UA_BOTTOM_MIN, SV_UA_BOTTOM_MAX);
}
