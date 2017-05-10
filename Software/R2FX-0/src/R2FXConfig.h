/**
 *                ____  ____  _______  __
 *               |  _ \|___ \|  ___\ \/ /
 *               | |_) | __) | |_   \  / 
 *               |  _ < / __/|  _|  /  \ 
 *               |_| \_\_____|_|   /_/\_\                      
 *           -------------------------------
 *            Visual effects control system.
 *         
 * R2FXConfig.h - Stores configuation specific details about your astromech.
 * Copyright (c) 2015 Manny Garcia, written for the R2Builders group
 * 
 * BSD license, all text above must be included in any redistribution
**/


#ifndef R2FXConfig_h
#define R2FXConfig_h

/** Global **/
// Serial Configuration
#define SERIAL_BAUD_RATE 250000
// Random Seed Config
#define ANALOG_PIN_SEED 5
// Bluetooth shield configuration
//Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST)

#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7 
#define BLUEFRUIT_SPI_RST 6

/** Auto Dome **/
#define AUTO_DOME_ANALOG_PIN 1

#define PWM_MAX_TRAVEL_PER_MILLI 0.5

/** Body Servo Configuration  **/
#define BODY_PWM_SHIELD_ADDRESS 0x41
#define BODY_PWM_SHIELD_SERVO_FREQ 60
#define BODY_PWM_SHIELD_CHANNELS 9

#define SV_UA_TOP 0
#define SV_UA_IS_INVERSED false
#define SV_UA_TOP_MIN 150
#define SV_UA_TOP_MAX 600

#define SV_UA_BOTTOM 1
#define SV_UA_BOTTOM_IS_INVERSED false
#define SV_UA_BOTTOM_MIN 150
#define SV_UA_BOTTOM_MAX 600

#define SV_CBI 2
#define SV_CBI_IS_INVERSED false
#define SV_CBI_MIN 150
#define SV_CBI_MAX 600

#define SV_LOWER_CBI 3
#define SV_LOWER_CBI_IS_INVERSED false
#define SV_LOWER_CBI_MIN 150
#define SV_LOWER_CBI_MAX 600

#define SV_DPI 4
#define SV_DPI_IS_INVERSED false
#define SV_DPI_MIN 150
#define SV_DPI_MAX 600

#define SV_FL 5
#define SV_FL_IS_INVERSED false
#define SV_FL_MIN 150
#define SV_FL_MAX 600

#define SV_FR 6
#define SV_FR_IS_INVERSED false
#define SV_FR_MIN 150
#define SV_FR_MAX 600

#define SV_RL 7
#define SV_RL_IS_INVERSED false
#define SV_RL_MIN 150
#define SV_RL_MAX 600

#define SV_RR 8
#define SV_RR_IS_INVERSED false
#define SV_RR_MIN 150
#define SV_RR_MAX 600

/** Dome Servo Configuration **/
#define DOME_PWM_SHIELD_ADDRESS 0x40
#define DOME_PWM_SHIELD_SERVO_FREQ 60
#define DOME_PWM_SHIELD_CHANNELS 10

// Pie panels
#define SV_PPC 0
#define SV_PPC_IS_INVERSED false
#define SV_PPC_MIN 150
#define SV_PPC_MAX 600

#define SV_PP1 1
#define SV_PP1_IS_INVERSED false
#define SV_PP1_MIN 150
#define SV_PP1_MAX 600

#define SV_PP2 2
#define SV_PP2_IS_INVERSED false
#define SV_PP2_MIN 150
#define SV_PP2_MAX 600

// Skip HP and periscope panels

#define SV_PP5 3
#define SV_PP5_IS_INVERSED false
#define SV_PP5_MIN 150
#define SV_PP5_MAX 600

#define SV_PP6 4
#define SV_PP6_IS_INVERSED false
#define SV_PP6_MIN 150
#define SV_PP6_MAX 600

// Lower dome panels
#define SV_P1 5
#define SV_P1_IS_INVERSED false
#define SV_P1_MIN 150
#define SV_P1_MAX 600

#define SV_P2 6
#define SV_P2_IS_INVERSED false
#define SV_P2_MIN 150
#define SV_P2_MAX 600

#define SV_P3 7
#define SV_P3_IS_INVERSED false
#define SV_P3_MIN 150
#define SV_P3_MAX 600

#define SV_P4 8
#define SV_P4_IS_INVERSED false
#define SV_P4_MIN 150
#define SV_P4_MAX 600

// Non movable panels

#define SV_P7 8
#define SV_P7_IS_INVERSED false
#define SV_P7_MIN 150
#define SV_P7_MAX 600

// large panel
#define SV_PA 9
#define SV_PA_IS_INVERSED false
#define SV_PA_MIN 150
#define SV_PA_MAX 600

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

#endif // R2FXConfig_h
