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

#include <round/util/message.h>
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
  
  free(msg);

  return true;
}
