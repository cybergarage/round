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
  size_t n;
  
  if (!map)
    return false;
  
  if (map->table) {
    for (n = 0; n<ROUND_UTIL_MAP_TABLE_SIZE; n++) {
      if (!map->table[n])
        continue;
      round_map_objectlist_delete(map->table[n]);
    }
    free(map->table);
    map->table = NULL;
  }
  
  free(map);
  
  return true;
}

/****************************************
 * round_map_size
 ****************************************/

size_t round_map_size(RoundMap *map)
{
  size_t mapSize, n;
  
  if (!map || !map->table)
    return 0;

  mapSize = 0;
  for (n=0; n<ROUND_UTIL_MAP_TABLE_SIZE; n++) {
    if (!map->table[n])
      continue;
    mapSize += round_map_objectlist_size(map->table[n]);
  }
  
  return mapSize;
}

/****************************************
 * round_map_getefficiency
 ****************************************/

double round_map_getefficiency(RoundMap *map)
{
  size_t mapCnt, tableCnt, n;
  
  if (!map || !map->table)
    return 0.0;
  
  mapCnt = tableCnt = 0;
  for (n=0; n<ROUND_UTIL_MAP_TABLE_SIZE; n++) {
    if (!map->table[n])
      continue;
    mapCnt += round_map_objectlist_size(map->table[n]);
    tableCnt++;
  }
  
  return ((double)tableCnt/(double)mapCnt);
}


/****************************************
 * round_map_getkeycode
 ****************************************/

size_t round_map_getkeycode(RoundMap *map, const char *key)
{
  size_t keyCode, keySize, n;
  
  keyCode = 0;
  
  keySize = round_strlen(key);
  for (n=0; n<keySize; n++) {
    // TODO : Optimaze hash alogorithm
    keyCode += (ROUND_UTIL_MAP_TABLE_SIZE - key[n]);
    if ((SIZE_MAX/2) < keyCode) {
      keyCode = keyCode % ROUND_UTIL_MAP_TABLE_SIZE;
    }
  }
  
  return keyCode % ROUND_UTIL_MAP_TABLE_SIZE;
}

/****************************************
 * round_map_addmapobject
 ****************************************/

bool round_map_addmapobject(RoundMap *map, RoundMapObject *obj)
{
  char *key;
  size_t keyCode;
  
  if (!map || !obj)
    return false;
  
  key = round_map_object_getkey(obj);
  if (!key)
    return false;
  
  round_map_removeobjectbykey(map, key);
  
  keyCode = round_map_getkeycode(map, key);
  if (!map->table[keyCode]) {
    map->table[keyCode] = round_map_objectlist_new();
  }
  
  if (!map->table[keyCode])
    return false;

  return round_map_objectlist_add(map->table[keyCode], obj);
}

/****************************************
 * round_map_addmapobject
 ****************************************/

bool round_map_setobject(RoundMap *map, const char *key, void *obj)
{
  RoundMapObject *mapObj;
  
  mapObj = round_map_object_new();
  if (!obj)
    return false;
  
  if (!key)
    return false;
  
  round_map_object_setkey(mapObj, key);
  round_map_object_setobject(mapObj, obj);
  
  return round_map_addmapobject(map, mapObj);
}

/****************************************
 * round_map_removeobjectbykey
 ****************************************/

bool round_map_removeobjectbykey(RoundMap *map, const char *key)
{
  RoundMapObject *obj;
  
  if (!map || !key)
    return false;
  
  obj = round_map_getmapobjectbykey(map, key);
  if (!obj)
    return false;
  
  round_map_object_remove(obj);
  round_map_object_delete(obj);
  
  return true;
}

/****************************************
 * round_map_getmapobjectbykey
 ****************************************/

RoundMapObject *round_map_getmapobjectbykey(RoundMap *map, const char *key)
{
  RoundMapObject *mapObj;
  size_t keyCode;
  
  if (!map)
    return NULL;
  
  keyCode = round_map_getkeycode(map, key);
  if (!map->table[keyCode])
    return NULL;
  
  for (mapObj = round_map_objectlist_gets(map->table[keyCode]); mapObj; mapObj = round_map_object_next(mapObj)) {
    if (round_map_object_iskey(mapObj, key))
      return mapObj;
  }
  
  return NULL;
}

/****************************************
 * round_map_getobjectbykey
 ****************************************/

void *round_map_getobjectbykey(RoundMap *map, const char *key)
{
  RoundMapObject *mapObj;

  mapObj = round_map_getmapobjectbykey(map, key);
  if (!mapObj)
    return NULL;
  
  return round_map_object_getobject(mapObj);
}


