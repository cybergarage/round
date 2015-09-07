/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/map.h>

/****************************************
 * round_map_new
 ****************************************/

RoundMap *round_map_new()
{
  RoundMap *map;
  
  map = (RoundMap *)malloc(sizeof(RoundMap));
  
  if (!map)
    return NULL;
  
  map->table = calloc(ROUND_UTIL_MAP_TABLE_SIZE, sizeof(RoundList *));
  if (!map->table) {
    round_map_delete(map);
    return NULL;
  }
  
  return map;
}

/****************************************
 * round_map_delete
 ****************************************/

bool round_map_delete(RoundMap *map)
{
  if (!map)
    return false;
  
  if (map->table) {
    free(map->table);
    map->table = NULL;
  }
  
  free(map);
  
  return true;
}
