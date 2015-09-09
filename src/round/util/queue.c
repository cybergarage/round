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

#define round_queue_clear(queue) round_list_clear((RoundList *)queue, NULL)
#define round_queue_gets(queue) round_list_next((RoundList *)queue)
#define round_queue_add(queue, obj) round_list_add((RoundList *)queue, (RoundList *)obj)

/****************************************
* round_queue_new
****************************************/

RoundQueue *round_queue_new(void)
{
  RoundQueue *queue;

  queue = (RoundQueue *)malloc(sizeof(RoundQueue));

  if (!queue)
    return NULL;

  round_list_header_init((RoundList *)queue);

  return queue;
}

/****************************************
* round_queue_delete
****************************************/

bool round_queue_delete(RoundQueue *queue)
{
  if (!queue)
    return false;
  
  round_queue_clear(queue);
  
  free(queue);
  
  return true;
}

/****************************************
 * round_queue_push
 ****************************************/

bool round_queue_push(RoundQueue *queue, RoundQueueObject *obj)
{
  if (!queue)
    return false;
  return round_queue_add(queue, obj);
}

/****************************************
 * round_queue_pop
 ****************************************/

bool round_queue_pop(RoundQueue *queue, RoundQueueObject **obj)
{
  RoundList *topObj;
  
  if (!queue)
    return false;
  
  topObj = round_queue_gets(queue);
  if (!topObj)
    return false;
  
  if (!round_queue_object_remove(topObj))
    return false;
  
  *obj = (RoundQueueObject *)topObj;
  
  return true;
}
