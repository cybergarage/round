/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/node_internal.h>

/****************************************
* round_local_node_message_new
****************************************/

RoundMessage *round_local_node_message_new()
{
  RoundMessage *msg;
  RoundLocalMessageData *msgData;
  
  msg = round_message_new();
  if (!msg)
    return NULL;

  msgData = malloc(sizeof(msgData));
  if (!msgData) {
    round_message_delete(msg);
    return NULL;
  }

  msgData->resObj = NULL;
  msgData->err = NULL;

  round_message_setuserdata(msg, msgData);
  
  return msg;
}

/****************************************
 * round_local_node_message_delete
 ****************************************/

bool round_local_node_message_delete(RoundMessage *msg)
{
  RoundLocalMessageData *msgData;

  if (!msg)
    return true;
  
  msgData = (RoundLocalMessageData *)round_message_getuserdata(msg);
  if (msgData) {
    free(msgData);
  }
  
  return round_message_delete(msg);
}

/****************************************
 * round_local_node_message_seterror
 ****************************************/

bool round_local_node_message_seterror(RoundMessage *msg, RoundError *err)
{
  RoundLocalMessageData *msgData;
  
  if (!msg)
    return false;
  
  msgData = (RoundLocalMessageData *)round_message_getuserdata(msg);
  if (!msgData)
    return false;
  
  msgData->err = err;
  
  return true;
}

/****************************************
 * round_local_node_message_geterror
 ****************************************/

RoundError *errround_local_node_message_geterror(RoundMessage *msg)
{
  RoundLocalMessageData *msgData;
  
  if (!msg)
    return NULL;
  
  msgData = (RoundLocalMessageData *)round_message_getuserdata(msg);
  if (!msgData)
    return NULL;
  
  return msgData->err;
}

/****************************************
 * round_local_node_message_setresponsejsonobject
 ****************************************/

bool round_local_node_message_setresponsejsonobject(RoundMessage *msg, RoundJSONObject *resObj)
{
  RoundLocalMessageData *msgData;
  
  if (!msg)
    return false;
  
  msgData = (RoundLocalMessageData *)round_message_getuserdata(msg);
  if (!msgData)
    return false;
  
  *msgData->resObj = resObj;
  
  return true;
}

/****************************************
 * round_local_node_message_getresponsejsonobject
 ****************************************/

RoundJSONObject *round_local_node_message_getresponsejsonobject(RoundMessage *msg)
{
  RoundLocalMessageData *msgData;
  
  if (!msg)
    return NULL;
  
  msgData = (RoundLocalMessageData *)round_message_getuserdata(msg);
  if (!msgData)
    return NULL;
  
  return *msgData->resObj;
}
