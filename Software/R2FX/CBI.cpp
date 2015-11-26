/**
  CBI.h - A library used to manage the CBI and DPL displays developed 
  Micheal Erwin.  Big thanks to him and Glyn Harper for making this hardware
  continously available to club members.
  
  Copyright (c) 2015 Manny Garcia, written for the R2Builders Group

  BSD license, all text above must be included in any redistribution
**/

#include "LedControl.h"
#include "CBI.h"
#include "BodyConfig.h"

/**
Initialize the displays by seting the brightness and clearing the display, just in case.
*/
CBI::CBI() {
  for (int i=0; i < LC_NUM_DEVICES; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, BODY_DISPLAY_INTENSITY);
    lc.clearDisplay(i);
  }
}

void CBI::randomCBISeq(int batLevel) {
  if ((millis() - lastCBIUpdate) > CBI_DISPLAY_DELAY) {
  // generate the random sequence
    for (int i = 0; i <= 6; i++) {
      byte b = random(256);
      if (i >= 4) {
        // set bit for battery level lights to 0
        b ^= (-0 ^ b) & (1 << 2);
        if (batLevel > 80 && i == 4) {
          b = b | B00000100;
        } else if (batLevel > 30 && i == 5) {
          b = b | B00000100;
        } else if (batLevel > 5 && i == 6) {
          b = b | B00000100;
        }
      }
      lc.setRow(0, i, b);
    }
    lastCBIUpdate = millis();
  }
}

void CBI::randomDPLSeq() {
  if ((millis() - lastDPLUpdate) > DPL_DISPLAY_DELAY) {
    for (int i = 0; i <= 6; i++) {
      lc.setRow(1,i,random(256));
    }
    lastDPLUpdate = millis();
  }
}

void CBI::displayChargeLevel(int level) {
  if (level > 80) {
    lc.setLed(0, 4, 5, true);
    lc.setLed(0, 5, 5, true);
    lc.setLed(0, 6, 5, true);
  } else if (level > 30) {
    lc.setLed(0, 4, 5, false);
    lc.setLed(0, 5, 5, true);
    lc.setLed(0, 6, 5, true);
  } else if (level > 5) {
    lc.setLed(0, 4, 5, false);
    lc.setLed(0, 5, 5, false);
    lc.setLed(0, 6, 5, true);
  } else {
    lc.setLed(0, 4, 5, false);
    lc.setLed(0, 5, 5, false);
    lc.setLed(0, 6, 5, false);
  }
}

void CBI::allOn(bool isOn) {
  byte val = B11111111;
  if (!isOn) {
    val = B00000000;
  }
  for (int i = 0; i <= 6; i++) {
    lc.setRow(0, i, val);
  }
}

// Credit goes to Micheal Erwin!
void CBI::heartSEQ() {
  // Step 0
  lc.setRow(0, 0, B01110000);
  lc.setRow(0, 1, B00100000);
  lc.setRow(0, 2, B00100000);
  lc.setRow(0, 3, B01110000);
  delay(1000);
  // Step 1
  lc.setRow(0, 0, B01010001);
  lc.setRow(0, 1, B11111000);
  lc.setRow(0, 2, B01110000);
  lc.setRow(0, 3, B00100000);
  delay(1000);
  // Step 1
  lc.setRow(0, 0, B01010001);
  lc.setRow(0, 1, B01010001);
  lc.setRow(0, 2, B01010001);
  lc.setRow(0, 3, B01110000);
  delay(1000);
}

void CBI::isCBIEnabled(bool enable) {
  for (int i = 0; i <= 6; i++) {
    lc.setRow(0, i, B00000000);
  }
  lc.shutdown(0, !enable);
  hasCBIOn = enable;
}

void CBI::isDPLEnabled(bool enable) {
  for (int i = 0; i <= 6; i++) {
    lc.setRow(1, i, B00000000);
  }
  lc.shutdown(1, !enable);
  hasDPLOn = enable;
}

bool CBI::isCBIEnabled() {
  return hasCBIOn;
}

bool CBI::isDPLEnabled() {
  return hasDPLOn;
}
