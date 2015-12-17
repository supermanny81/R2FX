/**
*                   ~~~
*                  \_0_/
*                   | | ___---___
*                 ____  ____  _______  __
*                |  _ \|___ \|  ___\ \/ /
*              / | |_) | __) | |_   \  / \
*            /   |  _ < / __/|  _|  /  \   \
*           |    |_| \_\_____|_|   /_/\_\   |
*      ___  |-------------------------------|  ___
*      |  |_| Visual effects control system |_|  |
*      |          =====================          |
*
* Copyright (c) 2015 Manny Garcia, written for the R2Builders Group
*
* BSD license, all text above must be included in any redistribution
*/

#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_FRAM_I2C.h>
#include "Wire.h"
#include "CBI.h"
#include "VoltageDivider.h"
#include "R2FXConfig.h"
#include "TimedServos.h"
#include "Utility.h"
#include "R2FXMessageHandler.h"

CBI* cbi = CBI::getInstance();
TimedServos* ts = TimedServos::getInstance();
R2FXMessageHandler message = R2FXMessageHandler();

/**
 * Setup for each of R2 subsystems here, each 
 */
void setup() {
  // initialize random seed with reading from a PIN that is not used.
  randomSeed(analogRead(ANALOG_PIN_SEED));
  // Used for debugging
  Serial.begin(SERIAL_BAUD_RATE);
  message.clearCommand();
  Serial.println(F("R2FX v1.1"));
  ts->setup();
  cbi->setup();
  // use fast IIC
  TWBR = 12; // upgrade to 400KHz!

  VoltageDivider::getInstance()->setup(VD_ANALOG_VIN_PIN, VD_RESISTOR_1,
                                      VD_RESISTOR_2, VD_MIN_VOLTAGE,
                                      VD_MAX_VOLTAGE);
}

void loop() {
  message.loop();
  ts->loop();
  cbi->loop();
}
