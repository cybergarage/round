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
* round_map_object_new
****************************************/

RoundMapObject *round_map_object_new(void) {
  RoundMapObject *obj;

  obj = (RoundMapObject *)malloc(sizeof(RoundMapObject));

  if (!obj)
    return NULL;

  round_list_node_init((RoundList *)obj);

  obj->key = NULL;
  obj->obj = NULL;
  obj->objDestFunc = NULL;

  return obj;
}

/****************************************
* round_map_object_delete
****************************************/

bool round_map_object_delete(RoundMapObject *obj) {
  if (!obj)
    return false;

  round_list_remove((RoundList *)obj);

  if (obj->key) {
    free(obj->key);
  }

  if (obj->obj && obj->objDestFunc) {
    obj->objDestFunc(obj->obj);
  }

  free(obj);

  return true;
}
