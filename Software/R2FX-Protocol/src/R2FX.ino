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
#include "Wire.h"
#include "R2FXConfig.h"
#include "Utility.h"
#include "R2FXMessageHandler.h"
#include "MemFree.h"

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
}

void loop() {
  message.loop();
}
