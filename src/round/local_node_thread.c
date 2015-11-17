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
  if (!thread)
    return;
  
  RoundLocalNode *node = (RoundLocalNode *)round_thread_getuserdata(thread);
  if (!node)
    return;

  RoundMessage *msg;
  RoundError *err;
  RoundJSONObject **resObj;

  while (round_local_node_isrunning(node)) {
    msg = NULL;
    round_message_manager_waitmessage(node->msgMgr, &msg);
    if (!msg)
      break;

    err = round_local_node_message_geterror(msg);
    resObj = round_local_node_message_getresponsejsonobject(msg);

    round_local_node_execmessage(node, msg, resObj, err);

    if (round_message_isnotifyenabled(msg)) {
      round_message_notify(msg);
    }
    else {
      if (*resObj) {
        round_json_object_delete(*resObj);
      }
    }

    round_local_node_message_delete(msg);
  }
}
