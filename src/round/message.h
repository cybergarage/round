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
#include <round/util/queue.h>
#include <round/util/semaphore.h>
#include <round/util/mutex.h>
#include <round/util/strings.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundMessage {
  ROUND_LIST_STRUCT_MEMBERS
  
  byte *data;
  size_t dataLen;
  
  void *userData;
} RoundMessage;

typedef struct {
  RoundQueue *queue;
  RoundSemaphore *sem;
  RoundMutex *mutex;
} RoundMessageManager;

/****************************************
* Function
****************************************/

RoundMessage *round_message_new(void);
bool round_message_delete(RoundMessage *msg);
bool round_message_clear(RoundMessage *msg);

bool round_message_setdata(RoundMessage *msg, byte *data, size_t dataLen);
bool round_message_setstring(RoundMessage *msg, const char *str);

#define round_message_getdata(msg)  (msg->data)
#define round_message_getstring(msg)  ((const char *)msg->data)
#define round_message_getdatasize(msg)  (msg->dataLen)
  
#define round_message_setuserdata(msg, data) (msg->userData = data)
#define round_message_getuserdata(msg)  (msg->userData)

#define round_message_next(msg) (RoundMessage *)round_list_next((RoundList *)msg)
#define round_message_remove(msg) round_list_remove((RoundList *)msg)
  
/****************************************
 * Function (Message Manager)
 ****************************************/
  
RoundMessageManager *round_message_manager_new(void);
bool round_message_manager_delete(RoundMessageManager *mgr);
bool round_message_manager_clear(RoundMessageManager *mgr);

bool round_message_manager_pushmessage(RoundMessageManager *mgr, RoundMessage *msg);
bool round_message_manager_waitmessage(RoundMessageManager *mgr, RoundMessage **msg);
  
#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
