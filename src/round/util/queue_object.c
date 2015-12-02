/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/queue.h>

/****************************************
* round_queue_object_new
****************************************/

RoundQueueObject* round_queue_object_new(void)
{
  RoundQueueObject* obj;

  obj = (RoundQueueObject*)malloc(sizeof(RoundQueueObject));

  if (!obj)
    return NULL;

  round_list_node_init((RoundList*)obj);

  obj->userData = NULL;

  return obj;
}

/****************************************
* round_queue_object_delete
****************************************/

bool round_queue_object_delete(RoundQueueObject* obj)
{
  if (!obj)
    return false;

  round_queue_object_remove(obj);

  free(obj);

  return true;
}
