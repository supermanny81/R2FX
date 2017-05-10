#ifndef DOME_H_
#define DOME_H_

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <LedControl.h>

#define DEGREES_TO_OFFSET 45
#define ROTARY_POT_PIN 2
#define ROTARY_POT_MIN 50
#define ROTARY_POT_MAX 900

class Dome {
  private:
    // select the input pin for the potentiometer
    int potPin = ROTARY_POT_PIN;

    //sensor reding and variables used to transform the value to desired poistion
    int val = 0;
    int rawDegree = 0;    // the position of the dome, 0 is facing forward
    int adjustDegree = DEGREES_TO_OFFSET;
    int degree = 0;

    // starter values
    int minPot = ROTARY_POT_MIN;
    int maxPot = ROTARY_POT_MAX;

    Dome() {};
    Dome(Dome const&); // copy disabled
    void operator=(Dome const&); // assigment disabled

  public:
    /**
      Returns the instance of this class.  We want to prevent multiple copies of this class
      being instatiated and taking memory.
    */
    static Dome* getInstance();
    int getDomePosition();
    /**
     * Sets the degrees the dome is facing.
     */
    void loop();
};
#endif //DOME_H_
