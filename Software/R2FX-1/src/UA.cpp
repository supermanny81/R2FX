#include "UA.h"

UA::UA() {
  ts->servoBoards[SV_UA_BOARD].channels[SV_UA_TOP].isInversed = SV_UA_IS_INVERSED;
  ts->servoBoards[SV_UA_BOARD].channels[SV_UA_TOP].srvMin = SV_UA_TOP_MIN;
  ts->servoBoards[SV_UA_BOARD].channels[SV_UA_TOP].srvMax = SV_UA_TOP_MAX;

  ts->servoBoards[SV_UA_BOARD].channels[SV_UA_BOTTOM].isInversed = SV_UA_BOTTOM_IS_INVERSED;
  ts->servoBoards[SV_UA_BOARD].channels[SV_UA_BOTTOM].srvMin = SV_UA_BOTTOM_MIN;
  ts->servoBoards[SV_UA_BOARD].channels[SV_UA_BOTTOM].srvMax = SV_UA_BOTTOM_MAX;
  Log.notice(F("UA setup." CR));
}

UA* UA::getInstance() {
  static UA ua;
  return &ua;
}

void UA::setup() {
  closeAll();
}

void UA::setUpperArmPosition(byte pos, int timeAllotted) {
  ts->setServoPosition(SV_UA_BOARD, SV_UA_TOP, pos, timeAllotted);
  Log.notice(F("Setting top UA to: %d" CR), pos);
}

void UA::setLowerArmPosition(byte pos, int timeAllotted) {
  ts->setServoPosition(SV_UA_BOARD, SV_UA_BOTTOM, pos, timeAllotted);
  Log.notice(F("Setting bottom UA to: %d" CR), pos);
}

void UA::toggleUpper() {
  byte pos = 0;
  if (!is_top_open) {
    pos = 127;
  }
  is_top_open = !is_top_open;
  setUpperArmPosition(pos);
}

void UA::toggleLower() {
  byte pos = 0;
  if (!is_bottom_open) {
    pos = 127;
  }
  is_bottom_open = !is_bottom_open;
  setLowerArmPosition(pos);
}

void UA::openAll() {
  is_top_open = false;
  is_bottom_open = false;
  toggleUpper();
  toggleLower();
}

void UA::closeAll() {
  is_top_open = true;
  is_bottom_open = true;
  toggleUpper();
  toggleLower();
}
