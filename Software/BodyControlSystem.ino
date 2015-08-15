#include "Wire.h"
#include "CBI.h"
#include "VoltageDivider.h"
#include "BodyConfig.h"

CBI cbi = CBI();
VoltageDivider vd = VoltageDivider(VD_ANALOG_VIN_PIN, VD_RESISTOR_1, 
  VD_RESISTOR_2, VD_MIN_VOLTAGE, VD_MAX_VOLTAGE);

bool isCBIOn = false;

void setup() {
  // initialize random seed with reading from a PIN that is not used.
  randomSeed(analogRead(5));
  // Used for debugging
  Serial.begin(9600);
}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    byte incomingByte = Serial.read();
    if (incomingByte == 66) {
      isCBIOn = !isCBIOn;
    } else if (incomingByte == 'C') {
      cbi.enabled(true);
      cbi.heartSEQ();
      cbi.enabled(isCBIOn);
    }
    Serial.println(incomingByte, DEC);
  }
  
  if (isCBIOn) {
    cbi.enabled(isCBIOn);
    cbi.randomSeq(vd.getVCCInPct());
  }
  
}
