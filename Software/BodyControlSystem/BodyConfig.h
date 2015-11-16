/**
  BodyConfig.h - Stores configuation specific details about your astromech.
  Copyright (c) 2015 Manny Garcia, written for the R2Builders group

  BSD license, all text above must be included in any redistribution
**/

/** Global **/
// Serial Configuration
#define SERIAL_BAUD_RATE 250000
// Random Seed Config
#define ANALOG_PIN_SEED 5

/** Auto Dome **/
#define AUTO_DOME_ANALOG_PIN 1

/** Body Servo Configuration  **/
#define BODY_PWM_SHIELD_ADDRESS 0x40
#define BODY_PWM_SHIELD_SERVO_FREQ 60
#define BODY_PWM_SHIELD_CHANNELS 9
// Define in degrees
#define BODY_PWM_MAX_TRAVEL_PER_MILLI 0.5
#define SV_UA_TOP 0
#define SV_UA_TOP_MIN 150
#define SV_UA_TOP_MAX 600
#define SV_UA_BOTTOM 1
#define SV_UA_BOTTOM_MIN 150
#define SV_UA_BOTTOM_MAX 600
#define SV_CBI 2
#define SV_CBI_MIN 150
#define SV_CBI_MAX 600
#define SV_LOWER_CBI 3
#define SV_LOWER_CBI_MIN 150
#define SV_LOWER_CBI_MAX 600
#define SV_DPI 4
#define SV_DPI_MIN 150
#define SV_DPI_MAX 600
#define SV_FL 5
#define SV_FL_MIN 150
#define SV_FL_MAX 600
#define SV_FR 6
#define SV_FR_MIN 150
#define SV_FR_MAX 600
#define SV_RL 7
#define SV_RL_MIN 150
#define SV_RL_MAX 600
#define SV_RR 8
#define SV_RR_MIN 150
#define SV_RR_MAX 600

/** Charge Bay and Data Port **/
//SPI Configuration for CBI and DPL
#define SPI_DATA_PIN 13
#define SPI_CLOCK_PIN 12
#define SPI_CS_PIN 11

//LED Control, one Maxim 72XX for each of the CBI and DPL, CBI must be first.
#define LC_NUM_DEVICES 2

//Brightness scale from 0 to 15
#define BODY_DISPLAY_INTENSITY 15
#define CBI_DISPLAY_DELAY 300
#define DPL_DISPLAY_DELAY 100

/** Voltage Divider Configuation **/
#define VD_ANALOG_VIN_PIN 0
#define VD_RESISTOR_1 47000.0
#define VD_RESISTOR_2 24000.0
#define VD_MIN_VOLTAGE 10.5
#define VD_MAX_VOLTAGE 12.7
