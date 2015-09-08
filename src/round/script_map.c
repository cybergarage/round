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
#include <round/script_internal.h>

/****************************************
 * round_script_map_new
 ****************************************/

RoundMap *round_script_map_new()
{
  RoundMap *map;
  
  map = round_map_new();
  if (!map)
    return NULL;
  
  round_map_setmapobjectdestructor(map, (ROUND_MAP_OBJECT_DESTRUCTOR)round_script_delete);
  
  return map;
}
