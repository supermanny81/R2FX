#ifndef PERISCOPE_H_
#define PERISCOPE_H_

#include <ArduinoLog.h>
#include <Wire.h>

#define PERISCOPE_ADDRESS 0x20

class Periscope {
  private:
    boolean periscopeUp = false;
    boolean periscopeRandomFast = false; //5, then 4
    boolean periscopeSearchLightCCW = false; // send 7, then 3

    Periscope() {};
    Periscope(Periscope const&); // copy disabled
    void operator=(Periscope const&); // assigment disabled

  public:
    static Periscope* getInstance() {
      static Periscope periscope;
      return &periscope;
    }

    void sendCommand(byte cmd) {
      // 0: DO NOTHING - ALLOW I2C TO TAKE CONTROL
      // 1: DOWN POSITION - ALL OFF
      // 2: FAST UP - RANDOM LIGHTS
      // 3: SEARCHLIGHT - CCW
      // 4: RANDOM - FAST
      // 5: RANDOM - SLOW
      // 6: DAGOBAH - WHITE LIGHTS - FACE FORWARD
      // 7: SEARCHLIGHT CW
      byte dev_address = PERISCOPE_ADDRESS;
      Wire.beginTransmission(dev_address); // transmit to device #20
      Wire.write(cmd); // sends one byte 0011
      Wire.endTransmission(); // stop transmitting
      Log.notice(F("Sent command: %d to device ID: %d" CR), cmd, dev_address);
    }

    void toggleRandom() {
      if (periscopeRandomFast) {
        // periscope up/down
        sendCommand(4);
      } else {
        // periscope up/down
        sendCommand(5);
      }
      periscopeRandomFast = !periscopeRandomFast;
    }

    void toggleUpDown() {
      if (periscopeUp) {
        // periscope down
        sendCommand(1);
        periscopeSearchLightCCW = false;
        periscopeRandomFast =  false;
      } else {
        // periscope up/down
        sendCommand(2);
      }
      periscopeUp = !periscopeUp;
    }

    void toggleSearchMode() {
      if (periscopeSearchLightCCW) {
        // periscope up/down
        sendCommand(3);
      } else {
        // periscope up/down
        sendCommand(7);
      }
      periscopeSearchLightCCW = !periscopeSearchLightCCW;
    }

    void dagobah() {
      sendCommand(6);
      periscopeUp = true;
    }

};
#endif //PERISCOPE_H_
