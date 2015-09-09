/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_MESSAGE_H_
#define _ROUNDC_UTIL_MESSAGE_H_

#include <round/typedef.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Define
 ****************************************/

#define UECHO_THREAD_MIN_SLEEP 1000

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundMessage {
  bool headFlag;
  struct _RoundMessage *prev;
  struct _RoundMessage *next;
    
  void *userData;
} RoundMessage, RoundMessageQueue;

typedef struct {
  RoundMessageQueue *queue;
} RoundMessageManager;

/****************************************
* Function
****************************************/

RoundMessage *round_message_new(void);
bool round_message_delete(RoundMessage *msg);

#define round_message_setuserdata(msg, data) (msg->userData = data)
#define round_message_getuserdata(msg)  (msg->userData)

#define round_message_next(msg) (RoundMessage *)round_list_next((RoundList *)msg)
#define round_message_remove(msg) round_list_remove((RoundList *)msg)

/****************************************
* Function (Message Queue)
****************************************/

RoundMessageQueue *round_message_queue_new();
void round_message_queue_delete(RoundMessageQueue *queue);

#define round_message_queue_clear(queue) round_list_clear((RoundList *)queue, (ROUND_LIST_DESTRUCTORFUNC)round_message_delete)
#define round_message_queue_size(queue) round_list_size((RoundList *)queue)
#define round_message_queue_gets(queue) (RoundMessage *)round_list_next((RoundList *)queue)
#define round_message_queue_add(queue, msg) round_list_add((RoundList *)queue, (RoundList *)msg)
#define round_message_queue_remove(msg) round_list_remove((RoundList *)msg)

/****************************************
 * Function (Message Manager)
 ****************************************/
  
RoundMessageManager *round_message_manager_new(void);
bool round_message_manager_delete(RoundMessageManager *mgr);
bool round_message_manager_clear(RoundMessageManager *mgr);

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
