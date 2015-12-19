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
#include <limits.h>
#include <round/util/map.h>

/****************************************
 * round_map_getasciihash
 ****************************************/

size_t round_map_getasciihash(const char* key)
{
  size_t keyCode = 0;
  size_t keySize = round_strlen(key);
  size_t keyCodeMax = INT_MAX;
  size_t n;
  for (n = 0; n < keySize; n++) {
    // TODO : Optimaize distributionr
    keyCode += ((int)key[n]) * pow(0x80, n);
    if (keyCodeMax < keyCode) {
      keyCode = keyCode % keyCodeMax;
    }
  }

  return keyCode;
}
