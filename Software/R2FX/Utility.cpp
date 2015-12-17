#include "Utility.h"

//  write a float value to string, outstr is returned string.
char * Utility::floatToString(char * outstr, float value, int places, int minwidth, bool rightjustify) {
  int i, digit;
  int c = 0, tenscount = 0, extra = 0;
  int charcount = 1;
  float tens = 0.1;
  float tempfloat = value;
  // make sure we round properly. this could use pow from <math.h>,
  // but doesn't seem worth the import. if this rounding step isn't
  // here, the value 54.321 prints as 54.3209
  float d = 0.5;                               // calculate rounding term d:   0.5/pow(10,places)
  if (value < 0) d *= -1.0;
  for (i = 0; i < places; i++) d /= 10.0;      // divide by ten for each decimal place
  tempfloat +=  d;                             // this small addition, plus truncation, will round values properly

  if (value < 0)tempfloat *= -1.0;             // first get value tens to be the large power of ten less than value
  while ((tens * 10.0) <= tempfloat) {
    tens *= 10.0;
    tenscount += 1;
  }

  if (tenscount > 0) charcount += tenscount; else charcount += 1;
  if (value < 0) charcount += 1; charcount += 1 + places;

  minwidth += 1;                                // count the null final character
  if (minwidth > charcount) {
    extra = minwidth - charcount;
    charcount = minwidth;
  }

  if (extra > 0 and rightjustify) {
    for (int i = 0; i < extra; i++) {
      outstr[c++] = ' ';
    }
  }

  if (value < 0) outstr[c++] = '-';            // write the negative sign if needed

  if (tenscount == 0) outstr[c++] = '0';

  for (i = 0; i < tenscount; i++) {
    digit = (int) (tempfloat / tens);
    itoa(digit, &outstr[c++], 10);
    tempfloat = tempfloat - ((float)digit * tens);
    tens /= 10.0;
  }
  // if no places after decimal, stop now and return
  if (places > 0) outstr[c++] = '.';           // otherwise, write the point and continue on

  // now write out each decimal place by shifting digits one by one
  for (i = 0; i < places; i++) {               // into the ones place and writing the truncated value
    tempfloat *= 10.0;
    digit = (int) tempfloat;
    itoa(digit, &outstr[c++], 10);
    tempfloat = tempfloat - (float) digit;
  }  // once written, subtract off that digit

  if (extra > 0 and not rightjustify) {
    for (int i = 0; i < extra; i++) {
      outstr[c++] = ' ';
    }
  }

  outstr[c++] = '\0'; return outstr;
}

uint8_t Utility::toInt(char *arr, uint8_t pos, uint8_t nBytes) {
  String work = String();
  for (uint8_t i = 0; i < nBytes; i++) {
    work += String(arr[pos + i] - '0');
  }
  return work.toInt();
}

