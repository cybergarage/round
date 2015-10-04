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
* round_local_node_message_thread
****************************************/

void round_local_node_message_thread(RoundThread *thread)
{
  RoundLocalNode *node;
  RoundMessage *msg;
  RoundError *err;
  RoundJSONObject *resObj;
  
  if (!thread)
    return;
  
  node = (RoundLocalNode *)round_thread_getuserdata(thread);
  if (!node)
    return;

  err = round_error_new();
  if (!err)
    return;
  
  while (round_local_node_isrunning(node)) {
    round_message_manager_waitmessage(node->msgMgr, &msg);
    if (!msg)
      break;
    
    resObj = NULL;
    round_error_clear(err);

    round_local_node_execmessage(node, msg, &resObj, err);

    if (round_message_isnotifyenabled(msg)) {
      round_message_notify(msg);
    }
    else {
      if (resObj) {
        round_json_object_delete(resObj);
      }
    }

    round_message_delete(msg);
  }

  round_error_delete(err);
}
