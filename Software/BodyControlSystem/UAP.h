#ifndef UAP_h
#define UAP_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "BodyConfig.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"

class UAP {
  private:
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PWM_SHIELD_ADDRESS);
    
    void setServoPosition(int SRV_NUM, int SRV_POS, int SRV_MIN, int SRV_MAX);
    
  public:
    UAP();
    
    void setUATop(int degree);
    void setUABottom(int degree);
};

#endif // UAP.h
