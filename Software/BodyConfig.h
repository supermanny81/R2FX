/**
  BodyConfig.h - Stores configuation specific details about your droid.
  Copyright (c) 2015 Manny Garcia, written for the R2Builders group

  BSD license, all text above must be included in any redistribution
**/

//Body Servo Configuration
#define SV_CBI 0
#define SV_DPI 1
#define SV_UA_TOP 14
#define SV_UA_BOTTOM 15

//SPI Configuration for CBI and DPL
#define SPI_DATA_PIN 13
#define SPI_CLOCK_PIN 12
#define SPI_CS_PIN 11

//LED Control, we only use one Maxim 72XX
#define LC_NUM_DEVICES 1

#define CBI_DISPLAY_DELAY 300

//Voltage Divider Configuation
#define VD_ANALOG_VIN_PIN 0
#define VD_RESISTOR_1 47000.0
#define VD_RESISTOR_2 24000.0
#define VD_MIN_VOLTAGE 10.5
#define VD_MAX_VOLTAGE 12.7


