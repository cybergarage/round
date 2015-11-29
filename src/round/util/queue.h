/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_QUEUE_H_
#define _ROUND_UTIL_QUEUE_H_

#include <round/typedef.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundQueue {
  ROUND_LIST_STRUCT_MEMBERS
} RoundQueue;

typedef struct _RoundQueueObject {
  ROUND_LIST_STRUCT_MEMBERS
  
  void *userData;
} RoundQueueObject;
  
/****************************************
* Function (Message Queue)
****************************************/

RoundQueue *round_queue_new();
bool round_queue_delete(RoundQueue *queue);

#define round_queue_size(queue) round_list_size((RoundList *)queue)
  
bool round_queue_push(RoundQueue *queue, RoundQueueObject *obj);
bool round_queue_pop(RoundQueue *queue, RoundQueueObject **obj);

/****************************************
 * Function (Message Queue Object)
 ****************************************/
  
RoundQueueObject *round_queue_object_new(void);
bool round_queue_object_delete(RoundQueueObject *obj);

#define round_queue_object_remove(obj) round_list_remove((RoundList *)obj)

#define round_queue_object_setuserdata(obj, data) (obj->userData = data)
#define round_queue_object_getuserdata(obj) (obj->userData)

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
