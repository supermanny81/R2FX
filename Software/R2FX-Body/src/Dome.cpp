#include <ArduinoLog.h>
#include "Dome.h"

Dome* Dome::getInstance() {
  static Dome dome;
  return &dome;
};


void Dome::loop() {
  val = analogRead(potPin);
  if (val < minPot) {
    minPot = val;
  } else if (val > maxPot) {
    maxPot = val;
  }
  rawDegree = map(val, minPot, maxPot, 0, 359);
  degree = rawDegree - adjustDegree;
  if (degree < 0) {
    degree += 359;
  }
}

int Dome::getDomePosition() {
  return degree;
}
