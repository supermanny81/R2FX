#ifndef PADAWAN_FX_CONFIG_H_
#define PADAWAN_FX_CONFIG_H_

// get data types
#include <Arduino.h>

//************************* Automation Settings *****************************//
#define AUTO_TIME_MIN 5
#define AUTO_TIME_MAX 20

// a 4S pack should go up to 4*4.2V = 16.8V at full charge and go down to no less than 4*3.2V = 12.8V at full discharge
#define MIN_VOLTAGE 12.8
#define MAX_VOLTAGE 16.8
// S to Arduino Analog pin
// - to Arduino Ground


// Set the baude rate for the Syren motor controller
// for packetized options are: 2400, 9600, 19200 and 38400. I think you need to pick one that works
// and I think it varies across different firmware versions.
// for simple serial use 9600
const int DOMEBAUDRATE = 19200;

// 9600 is the default baud rate for Sabertooth packet serial.
const int STBAUDRATE = 19200;

// Define the neutral zones for each of the analog sticks
const int LEFT_HAT_X_NEUTRAL = 7500;
const int LEFT_HAT_Y_NEUTRAL = 7500;

const int RIGHT_HAT_X_NEUTRAL = 7500;
const int RIGHT_HAT_Y_NEUTRAL = 7500;

//************************** Set speed and turn speeds here************************************//
//set these 3 to whatever speeds work for you. 0-stop, 127-full speed.
const byte DRIVESPEED1 = 50;
//Recommend beginner: 50 to 75, experienced: 100 to 127, I like 100.
const byte DRIVESPEED2 = 100;
//Set to 0 if you only want 2 speeds.
const byte DRIVESPEED3 = 127;

byte drivespeed = DRIVESPEED1;

// the higher this number the faster the droid will spin in place, lower - easier to control.
// Recommend beginner: 40 to 50, experienced: 50 $ up, I like 70
const byte TURNSPEED = 70;

// Use a number up to 127 for serial
const byte DOMESPEED = 127;

// Ramping- the lower this number the longer R2 will take to speedup or slow down,
// change this by incriments of 1
const byte RAMPING = 4;

#endif //PADAWAN_FX_CONFIG_H_
