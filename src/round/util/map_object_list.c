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
* round_map_objectlist_new
****************************************/

RoundMapObjectList *round_map_objectlist_new(void)
{
  RoundMapObjectList *objs;

  objs = (RoundMapObjectList *)malloc(sizeof(RoundMapObjectList));
  if (!objs)
    return NULL;

  round_list_header_init((RoundList *)objs);
  
  objs->key = NULL;
  objs->obj = NULL;
  
  return objs;
}

/****************************************
* round_map_objectlist_delete
****************************************/

bool round_map_objectlist_delete(RoundMapObjectList *objs)
{
  if (!objs)
    return false;
  
  round_map_objectlist_clear(objs);

  free(objs);
  
  return true;
}
