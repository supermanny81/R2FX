#ifndef VOLTAGE_H_
#define VOLTAGE_H_

#include <ArduinoLog.h>

// defaults for a 4S LiPO battery on A2, if you are using something else, you
// need to call the setup function with the proper values
#define MIN_VOLTAGE 12.8
#define MAX_VOLTAGE 16.8
#define VOLTAGE_SENSOR_PIN A2

class Voltage {
  private:

    float _minVoltage = MIN_VOLTAGE;
    float _maxVoltage = MAX_VOLTAGE;
    int _pin = VOLTAGE_SENSOR_PIN;

    float volts = 0.00;
    byte percent = 0;
    Voltage() {};
    Voltage(Voltage const&); // copy disabled
    void operator=(Voltage const&); // assigment disabled

  public:
    static Voltage* getInstance() {
      static Voltage voltage;
      return &voltage;
    }

    void setup(int pin, float minVoltage, float maxVoltage) {
      _pin = pin;
      _minVoltage = minVoltage;
      _maxVoltage = maxVoltage;
    }

    void sample() {
      volts = (analogRead(_pin) / 1024.) * 25;
      percent = map(constrain(volts, _minVoltage, _maxVoltage),
                    _minVoltage, _maxVoltage, 0, 100);
    }

    float getVCC() {
      return volts;
    }

    byte getVCCPct() {
      return percent;
    }

};
#endif //VOLTAGE_H_
