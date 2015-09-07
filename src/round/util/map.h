/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_MAP_H_
#define _ROUNDC_UTIL_MAP_H_

#include <round/typedef.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Define
 ****************************************/

#define ROUND_UTIL_MAP_TABLE_SIZE 256
  
/****************************************
 * Data Type
 ****************************************/

typedef struct {
  RoundList **table;
} RoundMap;

/****************************************
 * Functions
 ****************************************/

RoundMap *round_map_new();
bool round_map_delete(RoundMap *map);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
