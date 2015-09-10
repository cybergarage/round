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

#define ROUND_MAP_DEFAULT_TABLE_SIZE 4096
#define ROUND_MAP_DEFAULT_HASH_FUNC round_map_getasciihash
  
/****************************************
 * Data Type
 ****************************************/

typedef void (*ROUND_MAP_OBJECT_DESTRUCTOR)(void *);
typedef size_t (*ROUND_MAP_HASH_FUNC)(const char *);

typedef struct _RoundMapObject {
  ROUND_LIST_STRUCT_MEMBERS

  char *key;
  void *obj;

  ROUND_MAP_OBJECT_DESTRUCTOR objDestFunc;
} RoundMapObject, RoundMapObjectList;
  
  
typedef struct {
  RoundMapObjectList **table;
  size_t tableSize;
  ROUND_MAP_OBJECT_DESTRUCTOR mapObjDestFunc;
  ROUND_MAP_HASH_FUNC mapHashFunc;
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

#define round_map_object_setobjectdestructor(mapObj, func) (mapObj->objDestFunc = func)
#define round_map_object_getobjectdestructor(mapObj) (mapObj->objDestFunc)

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
bool round_map_setobject(RoundMap *map, const char *key, void *object);
void *round_map_getobjectbykey(RoundMap *map, const char *key);
bool round_map_removeobjectbykey(RoundMap *map, const char *key);
size_t round_map_getkeycode(RoundMap *map, const char *key);
RoundMapObject *round_map_getmapobjectbykey(RoundMap *map, const char *key);

bool round_map_settablesize(RoundMap *map, size_t value);
#define round_map_gettablesize(map) (map->tableSize)
  
#define round_map_setmaphashfunc(map, func) (map->mapHashFunc = func)
#define round_map_getmaphashfunc(map) (map->mapHashFunc)
  
#define round_map_setmapobjectdestructor(map, func) (map->mapObjDestFunc = func)
#define round_map_getmapobjectdestructor(map) (map->mapObjDestFunc)
  
double round_map_getefficiency(RoundMap *map);
void round_map_printdistribution(RoundMap *map);

/****************************************
 * Function (Hash)
 ****************************************/

size_t round_map_getasciihash(const char *key);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
