/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <math.h>
#include <round/util/map.h>

/****************************************
 * round_map_getasciihash
 ****************************************/

size_t round_map_getasciihash(const char *key)
{
  size_t keyCode, keySize, n;
  
  keyCode = 0;
  
  keySize = round_strlen(key);
  for (n=0; n<keySize; n++) {
    // TODO : Optimaize distributionr
    keyCode += ((int)key[n]) * pow(0x80, n);
    if ((SIZE_MAX/2) < keyCode) {
      keyCode = keyCode % (SIZE_MAX/2);
    }
  }
  
  return keyCode;
}
