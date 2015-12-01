/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdlib.h>
#include <round/method.h>

/****************************************
 * round_method_map_new
 ****************************************/

RoundMap *round_method_map_new() {
  RoundMap *map;

  map = round_map_new();
  if (!map)
    return NULL;

  round_map_setmapobjectdestructor(
  map, (ROUND_MAP_OBJECT_DESTRUCTOR)round_method_delete);

  return map;
}
