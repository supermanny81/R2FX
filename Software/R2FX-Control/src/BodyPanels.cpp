#include "BodyPanels.h"
#include "R2FXEnums.h"

BodyPanels::BodyPanels() {
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_CB].isInversed = SV_CB_IS_INVERSED;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_CB].srvMin = SV_CB_MIN;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_CB].srvMax = SV_CB_MAX;

  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_LOWER_BAY].isInversed = SV_LOWER_BAY_IS_INVERSED;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_LOWER_BAY].srvMin = SV_LOWER_BAY_MIN;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_LOWER_BAY].srvMax = SV_LOWER_BAY_MAX;

  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_DP].isInversed = SV_DP_IS_INVERSED;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_DP].srvMin = SV_DP_MIN;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_DP].srvMax = SV_DP_MAX;

  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_FL].isInversed = SV_FL_IS_INVERSED;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_FL].srvMin = SV_FL_MIN;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_FL].srvMax = SV_FL_MAX;

  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_FR].isInversed = SV_FR_IS_INVERSED;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_FR].srvMin = SV_FR_MIN;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_FR].srvMax = SV_FR_MAX;

  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_RR].isInversed = SV_RR_IS_INVERSED;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_RR].srvMin = SV_RR_MIN;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_RR].srvMax = SV_RR_MAX;

  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_RR].isInversed = SV_RR_IS_INVERSED;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_RR].srvMin = SV_RR_MIN;
  ts->servoBoards[SV_BODY_PANEL_BOARD].channels[SV_RR].srvMax = SV_RR_MAX;
  Log.notice(F("Bodypanels setup." CR));
}

BodyPanels* BodyPanels::getInstance() {
  static BodyPanels bodyPanels;
  return &bodyPanels;
}

void BodyPanels::setup() {
  closeAll();
}

void BodyPanels::dplEnabled(bool enabled) {
  Wire.beginTransmission(BODY_FX_ADDRESS);
  Wire.write((byte) R2FXCommand::DPL_ENABLED);
  Wire.write(enabled);
  Wire.endTransmission();
  Log.notice(F("Sent command: %d to device ID: %d" CR),
    R2FXCommand::DPL_ENABLED, enabled, BODY_FX_ADDRESS);
}

void BodyPanels::cbiEnabled(bool enabled) {
  Wire.beginTransmission(BODY_FX_ADDRESS);
  Wire.write((byte) R2FXCommand::CBI_ENABLED);
  Wire.write(enabled);
  Wire.endTransmission();
  Log.notice(F("Sent command: %d to device ID: %d" CR),
    R2FXCommand::CBI_ENABLED, enabled, BODY_FX_ADDRESS);
}

void BodyPanels::setCBPos(byte pos, int timeAllotted) {
  if (pos > 0) {
    isCBOpen = true;
    cbiEnabled(true);
  } else {
    isCBOpen = false;
    cbiEnabled(false);
  }
  ts->setServoPosition(SV_BODY_PANEL_BOARD, SV_CB, pos, timeAllotted);
  Log.notice(F("Setting CB bay to: %d" CR), pos);
}

void BodyPanels::setLBPos(byte pos, int timeAllotted) {
  if (pos > 0) {
    isLBOpen = true;
    dplEnabled(true);
  } else {
    isLBOpen = false;
    dplEnabled(false);
  }
  ts->setServoPosition(SV_BODY_PANEL_BOARD, SV_LOWER_BAY, pos, timeAllotted);
  Log.notice(F("Setting LB bay to: %d" CR), pos);
}

void BodyPanels::setDPPos(byte pos, int timeAllotted) {
  if (pos > 0)
    isDPOpen = true;
  else
    isDPOpen = false;
  ts->setServoPosition(SV_BODY_PANEL_BOARD, SV_DP, pos, timeAllotted);
  Log.notice(F("Setting DP bay to: %d" CR), pos);
}

void BodyPanels::setFLPos(byte pos, int timeAllotted) {
  if (pos > 0)
    isFLOpen = true;
  else
    isFLOpen = false;
  ts->setServoPosition(SV_BODY_PANEL_BOARD, SV_FL, pos, timeAllotted);
  Log.notice(F("Setting FL bay to: %d" CR), pos);
}

void BodyPanels::setFRPos(byte pos, int timeAllotted) {
  if (pos > 0)
    isFROpen = true;
  else
    isFROpen = false;
  ts->setServoPosition(SV_BODY_PANEL_BOARD, SV_FR, pos, timeAllotted);
  Log.notice(F("Setting FR bay to: %d" CR), pos);
}

void BodyPanels::setRLPos(byte pos, int timeAllotted) {
  if (pos > 0)
    isRLOpen = true;
  else
    isRLOpen = false;
  ts->setServoPosition(SV_BODY_PANEL_BOARD, SV_RL, pos, timeAllotted);
  Log.notice(F("Setting RL bay to: %d" CR), pos);
}

void BodyPanels::setRRPos(byte pos, int timeAllotted) {
  if (pos > 0)
    isRROpen = true;
  else
    isRROpen = false;
  ts->setServoPosition(SV_BODY_PANEL_BOARD, SV_RR, pos, timeAllotted);
  Log.notice(F("Setting RR bay to: %d" CR), pos);
}

void BodyPanels::openAll() {
  setCBPos(127);
  setLBPos(127);
  setDPPos(127);
  setFLPos(127);
  setFRPos(127);
  setRLPos(127);
  setRRPos(127);
  isOpen = true;
}

void BodyPanels::closeAll() {
  setCBPos(0);
  setLBPos(0);
  setDPPos(0);
  setFLPos(0);
  setFRPos(0);
  setRLPos(0);
  setRRPos(0);
  isOpen = false;
}
