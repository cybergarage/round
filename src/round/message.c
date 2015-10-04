/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#if !defined (WIN32)
#include <signal.h>
#endif

#include <round/message.h>
#include <string.h>

/****************************************
* round_message_new
****************************************/

RoundMessage *round_message_new(void)
{
  RoundMessage *msg;

  msg = (RoundMessage *)malloc(sizeof(RoundMessage));

  if (!msg)
    return NULL;
  
  round_list_node_init((RoundList *)msg);
  
  msg->data = NULL;
  msg->dataLen = 0;

  return msg;
}

/****************************************
* round_message_delete
****************************************/

bool round_message_delete(RoundMessage *msg)
{
  if (!msg)
    return false;
  
  round_message_remove(msg);
  round_message_clear(msg);

  free(msg);

  return true;
}

/****************************************
 * round_message_clear
 ****************************************/

bool round_message_clear(RoundMessage *msg)
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

bool round_message_setdata(RoundMessage *msg, byte *data, size_t dataLen)
{
  if (!round_message_clear(msg))
    return false;
  
  msg->data = (byte *)malloc(dataLen);
  if (!msg->data)
    return false;

  memccpy(msg->data, data, sizeof(byte), dataLen);
  msg->dataLen = dataLen;
  
  return true;
}

/****************************************
 * round_message_setstring
 ****************************************/

bool round_message_setstring(RoundMessage *msg, const char *str)
{
  return round_message_setdata(msg, (byte *)str, (round_strlen(str)+1));
}
