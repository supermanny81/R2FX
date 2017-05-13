#ifndef BODY_PANELS_H
#define BODY_PANELS_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <ArduinoLog.h>

#include "TimedServos.h"

#define BODY_FX_ADDRESS 0x08

#define SV_BODY_PANEL_BOARD 1
#define SV_CB 2
#define SV_CB_IS_INVERSED true
#define SV_CB_MIN 300
#define SV_CB_MAX 490

#define SV_LOWER_BAY 3
#define SV_LOWER_BAY_IS_INVERSED false
#define SV_LOWER_BAY_MIN 310
#define SV_LOWER_BAY_MAX 480

#define SV_DP 4
#define SV_DP_IS_INVERSED true
#define SV_DP_MIN 325
#define SV_DP_MAX 500

#define SV_FL 5
#define SV_FL_IS_INVERSED true
#define SV_FL_MIN 330
#define SV_FL_MAX 510

#define SV_FR 6
#define SV_FR_IS_INVERSED false
#define SV_FR_MIN 200
#define SV_FR_MAX 380

#define SV_RL 7
#define SV_RL_IS_INVERSED false
#define SV_RL_MIN 300
#define SV_RL_MAX 400

#define SV_RR 8
#define SV_RR_IS_INVERSED false
#define SV_RR_MIN 300
#define SV_RR_MAX 400

class BodyPanels {

  private:
    bool isOpen = true;
    bool isCBOpen = true;
    bool isLBOpen = true;
    bool isDPOpen = true;
    bool isFLOpen = true;
    bool isFROpen = true;
    bool isRLOpen = true;
    bool isRROpen = true;

    TimedServos* ts = TimedServos::getInstance();
    BodyPanels();
    BodyPanels(BodyPanels const&); // copy disabled
    void operator=(BodyPanels const&); // assigment disabled
    void dplEnabled(bool enabled);
    void cbiEnabled(bool enabled);

  public:
    static BodyPanels* getInstance();
    void setup();

    void setCBPos(byte pos, int timeAllotted = 0);
    void setLBPos(byte pos, int timeAllotted = 0);
    void setDPPos(byte pos, int timeAllotted = 0);
    void setFLPos(byte pos, int timeAllotted = 0);
    void setFRPos(byte pos, int timeAllotted = 0);
    void setRLPos(byte pos, int timeAllotted = 0);
    void setRRPos(byte pos, int timeAllotted = 0);

    void openAll();
    void closeAll();
};
#endif //BODY_PANELS_H
