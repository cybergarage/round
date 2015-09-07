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
#include <round/util/strings.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Define
 ****************************************/

#define ROUND_UTIL_MAP_TABLE_SIZE 4096
  
/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundMapObject {
  bool headFlag;
  struct _RoundMapObject *prev;
  struct _RoundMapObject *next;

  char *key;
  void *obj;
} RoundMapObject, RoundMapObjectList;
  
typedef void (*ROUND_MAP_DESTRUCTORFUNC)(void *);
  
typedef struct {
  RoundMapObjectList **table;
  ROUND_MAP_DESTRUCTORFUNC destFunc;
} RoundMap;

/****************************************
 * Function
 ****************************************/
  
RoundMapObject *round_map_object_new(void);
bool round_map_object_delete(RoundMapObject *obj);
RoundMapObject *round_map_object_next(RoundMapObject *obj);

#define round_map_object_iskey(mapObj, value) (round_streq(mapObj->key, value))
#define round_map_object_setkey(mapObj, value) (round_strloc(value, &mapObj->key))
#define round_map_object_getkey(mapObj) (mapObj->key)

#define round_map_object_setobject(mapObj, value) (mapObj->obj = value)
#define round_map_object_getobject(mapObj) (mapObj->obj)

#define round_map_object_next(mapObj) ((RoundMapObject *)round_list_next((RoundList *)mapObj))
#define round_map_object_remove(mapObj) round_list_remove((RoundList *)mapObj)
  
/****************************************
 * Function (MapObject List)
 ****************************************/
  
RoundMapObjectList *round_map_objectlist_new(void);
bool round_map_objectlist_delete(RoundMapObjectList *objs);
  
#define round_map_objectlist_clear(objs) round_list_clear((RoundList *)objs, (ROUND_LIST_DESTRUCTORFUNC)round_map_object_delete)
#define round_map_objectlist_size(objs) round_list_size((RoundList *)objs)
#define round_map_objectlist_gets(objs) (RoundMapObject *)round_list_next((RoundList *)objs)
#define round_map_objectlist_add(objs,obj) round_list_add((RoundList *)objs, (RoundList *)obj)
  
/****************************************
 * Function (Map)
 ****************************************/

RoundMap *round_map_new();
bool round_map_delete(RoundMap *map);

size_t round_map_size(RoundMap *map);
bool round_map_addmapobject(RoundMap *map, RoundMapObject *obj);
bool round_map_removeobjectbykey(RoundMap *map, const char *key);
size_t round_map_getkeycode(RoundMap *map, const char *key);
RoundMapObject *round_map_getmapobjectbykey(RoundMap *map, const char *key);

bool round_map_setobject(RoundMap *map, const char *key, void *object);
void *round_map_getobjectbykey(RoundMap *map, const char *key);
  
double round_map_getefficiency(RoundMap *map);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
