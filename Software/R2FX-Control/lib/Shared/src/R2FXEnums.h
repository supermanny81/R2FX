#ifndef R2FX_ENUMS_H
#define R2FX_ENUMS_H

#ifdef ARDUINO
  #include <Arduino.h>
#endif

enum class R2FXCommand:unsigned byte {
  // BODY COMMANDS
  UA_ALL_POS = 179,
  UA_TOP_POS = 180,
  UA_BOTTOM_POS = 181,
  // reseverd 4 commands
  CBI_DPL_ENABLED = 185,
  DPL_ENABLED = 186,
  CBI_ENABLED = 187,
  CBI_VOLTAGE = 188,
  CBI_SEQ = 189,
  DP_POS = 190,
  CB_POS = 191,
  LB_POS = 192,
  FL_POS = 193,
  FR_POS = 194,
  RL_POS = 195,
  RR_POS = 196,

  // DOME COMMANDS
  DOME_POSITION = 127,

  // TELEMETRY AND MANAGEMENT COMMANDS
  VOLTAGE_PCT = 240
};

#endif
