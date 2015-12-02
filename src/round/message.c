/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#if !defined(WIN32)
#include <signal.h>
#endif

#include <round/message.h>
#include <string.h>

/****************************************
* round_message_new
****************************************/

RoundMessage* round_message_new(void)
{
  RoundMessage* msg;

  msg = (RoundMessage*)malloc(sizeof(RoundMessage));

  if (!msg)
    return NULL;

  round_list_node_init((RoundList*)msg);

  msg->data = NULL;
  msg->dataLen = 0;

  msg->userData = NULL;
  msg->sem = NULL;

  return msg;
}

/****************************************
* round_message_delete
****************************************/

bool round_message_delete(RoundMessage* msg)
{
  if (!msg)
    return false;

  round_message_remove(msg);
  round_message_clear(msg);

  if (msg->sem) {
    round_semaphore_cancel(msg->sem);
    round_semaphore_delete(msg->sem);
  }

  free(msg);

  return true;
}

/****************************************
 * round_message_clear
 ****************************************/

bool round_message_clear(RoundMessage* msg)
{
  if (!msg)
    return false;

  if (msg->data) {
    free(msg->data);
    msg->data = NULL;
  }

  msg->dataLen = 0;

  return true;
}

/****************************************
 * round_message_setdata
 ****************************************/

bool round_message_setdata(RoundMessage* msg, byte* data, size_t dataLen)
{
  if (!round_message_clear(msg))
    return false;

  msg->data = (byte*)malloc(dataLen);
  if (!msg->data)
    return false;

  memccpy(msg->data, data, sizeof(byte), dataLen);
  msg->dataLen = dataLen;

  return true;
}

/****************************************
 * round_message_setstring
 ****************************************/

bool round_message_setstring(RoundMessage* msg, const char* str)
{
  return round_message_setdata(msg, (byte*)str, (round_strlen(str) + 1));
}

/****************************************
 * round_message_setnotifyenabled
 ****************************************/

bool round_message_setnotifyenabled(RoundMessage* msg, bool flag)
{
  if (!msg)
    return false;

  if (flag) {
    if (msg->sem)
      return true;
    msg->sem = round_semaphore_new(0);
    return round_message_isnotifyenabled(msg);
  }

  if (msg->sem) {
    round_semaphore_delete(msg->sem);
    msg->sem = NULL;
  }

  return true;
}

/****************************************
 * round_message_isnotifyenabled
 ****************************************/

bool round_message_isnotifyenabled(RoundMessage* msg)
{
  if (!msg)
    return false;

  return (msg->sem) ? true : false;
}

/****************************************
 * round_message_notify
 ****************************************/

bool round_message_notify(RoundMessage* msg)
{
  if (!msg || !msg->sem)
    return false;

  return round_semaphore_post(msg->sem);
}

/****************************************
 * round_message_waitnotify
 ****************************************/

bool round_message_waitnotify(RoundMessage* msg)
{
  if (!msg || !msg->sem)
    return false;

  return round_semaphore_wait(msg->sem);
}

/****************************************
 * round_message_timedwaitnotify
 ****************************************/

bool round_message_timedwaitnotify(RoundMessage* msg, time_t timeoutSec)
{
  if (!msg || !msg->sem)
    return false;

  return round_semaphore_timedwait(msg->sem, timeoutSec);
}
