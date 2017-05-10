/**
                  ~~~
                 \_0_/
                  | | ___---___
                ____  ____  _______  __
               |  _ \|___ \|  ___\ \/ /
             / | |_) | __) | |_   \  / \
           /   |  _ < / __/|  _|  /  \   \
          |    |_| \_\_____|_|   /_/\_\   |
     ___  |-------------------------------|  ___
     |  |_|    drive and control system   |_|  |
     |          =====================          |

  Based on the execellent Padawan360 sketch by Dan Kraus, which was influenced by DanF's
  original Padawan control system.

  Hardware:
  Arduino Mega
  USB Host Shield from circuits@home, Keyes, or SainSmart
  Microsoft Xbox 360 Controller
  Xbox 360 USB Wireless Reciver
  Sabertooth Motor Controller
  Syren10 Motor Controller
  Sparkfun WAV Trigger

  Set Sabertooth 2x25/2x12 Dip Switches 1 and 2 Down, All Others Up (9600 baud)

    Mega         ST
    ====         ===========
    GND <------>  0v
    Tx1 <------>  S1

  For Syren10en Packetized Serial Set Switchs 1 & 2 Down, All Others Up (9600 baud)

    Mega         Syren
    ====         ===========
    GND <------>  0v
    Tx2 <------>  S1

  Connect 2 wires from the UNO to the WAV Trigger's serial connector:

    Mega         WAV Trigger
    ====         ===========
    GND <------> GND
    Tx3 <------> RX
    Rx3 <------> TX (Required)

    Power the WAV trigger separately.

*/
#include <ArduinoLog.h>
#include <Sabertooth.h>
#include <SyRenSimplified.h>
#include <Wire.h>
#include <XBOXRECV.h>

#include "PadawanFXConfig.h"
#include "Periscope.h"
#include "SoundFX.h"
#include "TrackConfig.h"
#include "UA.h"

// private project based libraries
#include "ArduinoUtil.h"
#include "TimedServos.h"
#include "TimedServos.cpp"
#include "WavTrigger2.h"
#include "WavTrigger2.cpp"
#include "Voltage.h"

Sabertooth Sabertooth2xXX(128, Serial1);
Sabertooth Syren10(128, Serial2);

// 0 = drive motors off ( right stick disabled ) at start
boolean isDriveEnabled = false;

// Automated function variables
// Used as a boolean to turn on/off automated functions like periodic random sounds and periodic dome turns
boolean isInAutomationMode = false;
unsigned long automateMillis = 0;
byte automateDelay = random(5, 20); // set this to min and max seconds between sounds

//How much the dome may turn during automation.
int turnDirection = 20;

// Action number used to randomly choose a sound effect or a dome turn
byte automateAction = 0;

char driveThrottle = 0;
char sticknum = 0;
char domeThrottle = 0;
char turnThrottle = 0;

LEDEnum ledState;
long ledStateUpdate = 0;
LEDModeEnum ledModeState;
long ledModeStateUpdate = 0;
byte ledScene = 0;
boolean isLedAnimate = false;
long ledAnimatedSince = 0;
long xboxBtnPressedSince = 0;

boolean firstLoadOnConnect = false;

ArduinoUtil util = ArduinoUtil();
USB Usb;
XBOXRECV Xbox(&Usb);

Periscope* periscope = Periscope::getInstance();
SoundFX* sfx = SoundFX::getInstance();
TimedServos* ts = TimedServos::getInstance();
UA* ua = UA::getInstance();
Voltage* voltage = Voltage::getInstance();

void setup() {
  Serial.begin(115200);
  // Wait for serial port to connect - used on Leonardo, Teensy and other boards with
  // built-in USB CDC serial connection
  while (!Serial);

  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
  Log.verbose(F("PadawanFX" CR));

  if (Usb.Init() == -1) {
    Log.fatal(F("\r\nOSC did not start" CR));
    while (1); //halt
  }

  Serial1.begin(STBAUDRATE);
  Sabertooth2xXX.setTimeout(950);

  Serial2.begin(DOMEBAUDRATE);
  Syren10.setTimeout(950);

  Serial3.begin(WAVBAUDRATE);
  sfx->setup(&Serial3);

  // The Sabertooth won't act on mixed mode packet serial commands until
  // it has received power levels for BOTH throttle and turning, since it
  // mixes the two together to get diff-drive power levels for both motors.
  Sabertooth2xXX.drive(0);
  Sabertooth2xXX.turn(0);

  // let the connected i2c slaves initialize
  delay(250);

  Wire.begin();
  // use fast IIC
  TWBR = 12; // upgrade to 400KHz!
  ts->setup();
  ua->setup();
}

void loop() {
  // used in testing, keeps track of the number of cycles being run
  util.countCycles();
  animateLed();
  Usb.Task();

  //if we're not connected, return so we don't bother doing anything else.
  // set all movement to 0 so if we lose connection we don't have a runaway droid!
  // a restraining bolt and jawa droid caller won't save us here!
  if (!Xbox.XboxReceiverConnected || !Xbox.Xbox360Connected[0]) {
    Sabertooth2xXX.drive(0);
    Sabertooth2xXX.turn(0);
    Syren10.motor(1, 0);
    firstLoadOnConnect = false;
    xboxBtnPressedSince = 0;
    return;
  }

  // After the controller connects, Blink all the LEDs so we know drives are disengaged at start
  if (!firstLoadOnConnect) {
    firstLoadOnConnect = true;
    isDriveEnabled = false;
    sfx->play(CONTROLLER_CONNECTED);
    setLedMode(ROTATING, 0);
  }

  // enable / disable right stick (droid movement) & play a sound to signal motor state
  if (Xbox.getButtonClick(START, 0)) {
    if (isDriveEnabled) {
      isDriveEnabled = false;
      setLedMode(ROTATING, 0);
      sfx->play(random(HUM_SND_START, HUM_SND_END));
    } else {
      isDriveEnabled = true;
      sfx->play(PROC_SND_START);
      // //When the drive is enabled, set our LED accordingly to indicate speed
      if (drivespeed == DRIVESPEED1) {
        setLedOn(LED1, 0);
      } else if (drivespeed == DRIVESPEED2 && (DRIVESPEED3 != 0)) {
        setLedOn(LED2, 0);
      } else {
        setLedOn(LED3, 0);
      }
    }
  }

  //Toggle automation mode with the BACK button
  if (Xbox.getButtonClick(BACK, 0)) {
    if (isInAutomationMode) {
      isInAutomationMode = false;
      automateAction = 0;
      sfx->play(PROC_SND_START);
    } else {
      isInAutomationMode = true;
      sfx->play(random(PROC_SND_START + 1, PROC_SND_END));
    }
  }

  // UP on control pad
  if (Xbox.getButtonClick(UP, 0)) {
    if (Xbox.getButtonPress(R1, 0)) {
      sfx->volUp();
    } else if (Xbox.getButtonPress(L1, 0)) {
      periscope->dagobah();
    } else {
      ua->openAll();
    }
  }

  // DOWN on control pad
  if (Xbox.getButtonClick(DOWN, 0)) {
    if (Xbox.getButtonPress(R1, 0)) {
      sfx->volDown();
    } else if (Xbox.getButtonPress(L1, 0)) {
      periscope->toggleUpDown();
    } else {
      ua->closeAll();
    }
  }

  // LEFT on control pad
  if (Xbox.getButtonClick(LEFT, 0)) {
    if (Xbox.getButtonPress(R1, 0)) {
      // Nothing... yet
    } else if (Xbox.getButtonPress(L1, 0)) {
      periscope->toggleRandom();
    } else {
      ua->toggleUpper();
    }
  }

  // RIGHT on control pad
  if (Xbox.getButtonClick(RIGHT, 0)) {
    //volume down
    if (Xbox.getButtonPress(R1, 0)) {
      //Nothing.... yet
    } else if (Xbox.getButtonPress(L1, 0)) {
      periscope->toggleSearchMode();
    } else {
      ua->toggleLower();
    }
  }

  // Y Button and Y combo buttons
  if (Xbox.getButtonClick(Y, 0)) {
    if (Xbox.getButtonPress(L1, 0)) {
      sfx->play(random(LEIA_SND_START, LEIA_SND_END));
    } else if (Xbox.getButtonPress(L2, 0)) {
      sfx->play(random(SCREAM_SND_START, SCREAM_SND_END));
    } else if (Xbox.getButtonPress(R1, 0)) {
      sfx->play(SW_SND_THEME);
    } else if (Xbox.getButtonPress(R2, 0)) {
      sfx->play(PATROL_SND);
    } else {
      sfx->play(random(HUM_SND_START, HUM_SND_END));
    }
  }

  // X Button and X combo Buttons
  if (Xbox.getButtonClick(X, 0)) {
    if (Xbox.getButtonPress(L1, 0)) {
      sfx->play(random(CHAT_SND_START, CHAT_SND_END));
    } else if (Xbox.getButtonPress(L2, 0)) {
      sfx->play(random(WHISTLE_SND_START, WHISTLE_SND_END));
    } else if (Xbox.getButtonPress(R1, 0)) {
      sfx->play(EMPIRE_SND_THEME);
    } else if (Xbox.getButtonPress(R2, 0)) {
      sfx->play(random(HOLIDAY_MUS_START, HOLIDAY_MUS_END));
    } else {
      sfx->play(random(GEN_SND_START, GEN_SND_END));
    }
  }

  // A Button and A combo Buttons
  if (Xbox.getButtonClick(A, 0)) {
    if (Xbox.getButtonPress(L1, 0)) {
      sfx->play(DOODOO_SND);
    } else if (Xbox.getButtonPress(L2, 0)) {
      sfx->play(OVERHERE_SND);
    } else if (Xbox.getButtonPress(R1, 0)) {
      sfx->play(CANTINA_SND_THEME);
    } else if (Xbox.getButtonPress(R2, 0)) {
      sfx->play(random(R2THEME_MUS_START, R2THEME_MUS_END));
    } else {
      sfx->play(random(HAPPY_SND_START, HAPPY_SND_END));
    }
  }

  // B Button and B combo Buttons
  if (Xbox.getButtonClick(B, 0)) {
    if (Xbox.getButtonPress(L1, 0)) {
      sfx->play(random(SAD_SND_START, SAD_SND_END));
    } else if (Xbox.getButtonPress(L2, 0)) {
      sfx->play(random(RANDOM_MUS_START, RANDOM_MUS_END));
    } else if (Xbox.getButtonPress(R1, 0)) {
      sfx->play(SW_CHORUS_THEME);
    } else if (Xbox.getButtonPress(R2, 0)) {
      sfx->play(ANNOYED_SND);
    } else {
      sfx->play(random(PROC_SND_START, PROC_SND_END));
    }
  }

  // get battery levels
  if (Xbox.getButtonClick(XBOX, 0)) {
    voltage->sample();
    Log.notice(F("Xbox Battery Level: %d"CR), Xbox.getBatteryLevel(0));
    Log.notice(F("System Battery Level: %s (%d percent)"CR), String(voltage->getVCC()).c_str(), voltage->getVCCPct());
    isLedAnimate = true;
  }

  // MOVE OUT THE WAY
  if (Xbox.getButtonClick(L3, 0))  {
    sfx->play(IMPERIAL_SIREN);
  }

  // Change drivespeed if drive is eanbled
  // Press Right Analog Stick (R3)
  // Set LEDs for speed - 1 LED, Low. 2 LED - Med. 3 LED High
  if (Xbox.getButtonClick(R3, 0) && isDriveEnabled) {
    //if in lowest speed
    if (drivespeed == DRIVESPEED1) {
      //change to medium speed
      drivespeed = DRIVESPEED2;
      setLedOn(LED2, 0);
    } else if (drivespeed == DRIVESPEED2 && (DRIVESPEED3 != 0)) {
      //change to high speed
      drivespeed = DRIVESPEED3;
      setLedOn(LED3, 0);
    } else {
      //we must be in high speed
      drivespeed = DRIVESPEED1;
      setLedOn(LED1, 0);
    }
    sfx->play(PROC_SND_START);
  }

  drive();
  isDisconnecting();
  automationMode();
  ts->loop();
}

void setLedMode(LEDModeEnum ledMode, uint8_t controller) {
  ledModeState = ledMode;
  Xbox.setLedMode(ledMode, 0);
  isLedAnimate = false;
  ledModeStateUpdate = millis();
}

void setLedOn(LEDEnum led, uint8_t controller) {
  ledState = led;
  Xbox.setLedOn(led, controller);
  isLedAnimate = false;
  ledStateUpdate = millis();
}

void animateLed() {
  if(isLedAnimate == true) {
    voltage->sample();
    if (ledAnimatedSince == 0) {
      ledAnimatedSince = millis();
      Xbox.setLedOn(chooseLED(Xbox.getBatteryLevel(0)*25), 0);
      ledScene++;
    } else if (millis() - ledAnimatedSince > 2000 && ledScene == 1) {
      Xbox.setLedOn(OFF, 0);
      ledScene++;
    } else if (millis() - ledAnimatedSince > 2500 && ledScene == 2) {
      Xbox.setLedOn(chooseLED(voltage->getVCCPct()), 0);
      ledScene++;
    } else if (millis() - ledAnimatedSince > 4500 && ledScene == 3) {
      Xbox.setLedOn(OFF, 0);
      ledScene++;
    } else if (millis() - ledAnimatedSince > 5000 && ledScene == 4) {
      if (ledStateUpdate > ledModeStateUpdate) {
        setLedOn(ledState, 0);
      } else {
        setLedMode(ledModeState, 0);
      }
      ledScene++;
    }
  } else {
    ledAnimatedSince = 0;
    ledScene = 0;
  }
}

LEDEnum chooseLED(byte level) {
  if (level > 75) {
    return LED4;
  } else if (level > 50) {
    return LED3;
  } else if (level > 25) {
    return LED2;
  } else if (level >=0) {
    return LED1;
  }
}

void drive() {
  // FOOT DRIVES
  // Xbox 360 analog stick values are signed 16 bit integer value
  // Sabertooth runs at 8 bit signed. -127 to 127 for speed (full speed reverse and full speed forward)
  // Map the 360 stick values to our min/max current drive speed
  if (abs((long) Xbox.getAnalogHat(RightHatY, 0)) > RIGHT_HAT_Y_NEUTRAL) {
    sticknum = (map(Xbox.getAnalogHat(RightHatY, 0), -32768, 32767, -drivespeed, drivespeed));
    if (driveThrottle < sticknum) {
      if (sticknum - driveThrottle < (RAMPING + 1) ) {
        driveThrottle += RAMPING;
      } else {
        driveThrottle = sticknum;
      }
    } else if (driveThrottle > sticknum) {
      if (driveThrottle - sticknum < (RAMPING + 1) ) {
        driveThrottle -= RAMPING;
      } else {
        driveThrottle = sticknum;
      }
    }
  } else {
    driveThrottle = 0;
  }

  if (abs((long) Xbox.getAnalogHat(RightHatX, 0)) > RIGHT_HAT_X_NEUTRAL) {
    turnThrottle = map(Xbox.getAnalogHat(RightHatX, 0), -32768, 32767, -TURNSPEED, TURNSPEED);
  } else {
    turnThrottle = 0;
  }

  // DRIVE!
  // right stick (drive)
  if (isDriveEnabled) {
    Sabertooth2xXX.turn(turnThrottle);
    Sabertooth2xXX.drive(driveThrottle);
  }

  // DOME DRIVE!
  if (abs((long) Xbox.getAnalogHat(LeftHatX, 0)) > LEFT_HAT_X_NEUTRAL) {
    domeThrottle = (map(Xbox.getAnalogHat(LeftHatX, 0), -32768, 32767, -DOMESPEED, DOMESPEED));
  } else {
    domeThrottle = 0;
  }
  Syren10.motor(1, domeThrottle);
}

/**
   Determines if the controller needs to be shutdown.  The disconnect signal is sent once the XBOX
   button has been pressed for more than 3s, a rumble will indicate the controller is being shutdown.
*/
void isDisconnecting() {
  if (Xbox.getButtonPress(XBOX, 0)) {
    if (xboxBtnPressedSince == 0) {
      xboxBtnPressedSince = millis();
    } else if (millis() - xboxBtnPressedSince >= 2000 && millis() - xboxBtnPressedSince < 2500) {
      Xbox.setRumbleOn(0, 127, 0);
      Log.warning(F("Shutting down controller.  Elapsed time: %d"CR), millis() - xboxBtnPressedSince);
    } else if (millis() - xboxBtnPressedSince >= 2500) {
      xboxBtnPressedSince = 0;
      Xbox.disconnect(0);
    }
  } else {
    xboxBtnPressedSince = 0;
  }
}

void automationMode() {
  // Plays random sounds or dome movements for automations when in automation mode
  if (isInAutomationMode) {
    unsigned long currentMillis = millis();
    if (currentMillis - automateMillis > (automateDelay * 1000)) {
      automateMillis = millis();
      automateAction = random(1, 5);
      if (automateAction > 1) {
        sfx->play(random(AUTO_SND_START, AUTO_SND_END));
      }
      if (automateAction < 4) {
        Syren10.motor(1, turnDirection);
        delay(750);
        Syren10.motor(1, 0);
        if (turnDirection > 0) {
          turnDirection = -45;
        } else {
          turnDirection = 45;
        }
      }
      // sets the mix, max seconds between automation actions - sounds and dome movement
      automateDelay = random(AUTO_TIME_MIN, AUTO_TIME_MAX);
    }
  }
}
