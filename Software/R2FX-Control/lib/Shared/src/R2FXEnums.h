#ifndef R2FX_ENUMS_H
#define R2FX_ENUMS_H
#include <Arduino.h>

enum class R2FXCommand:byte {
  CBI_DPL_DISABLE = 0x00,
  CBI_DPL_ENABLE = 0x01,
  DPL_DISABLE = 0x05,
  DPL_ENABLE = 0x06,
  CBI_DISABLE = 0x0A,
  CBI_ENABLE = 0x0B,
  CBI_HEART_SEQ = 0x0C,
  CBI_DISPLAY_VOLTAGE = 0x0D,
  // DOME
  DOME_POSITION = 0x14
};

#endif
