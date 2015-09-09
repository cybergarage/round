/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/message.h>

/****************************************
* round_message_queue_new
****************************************/

RoundMessageQueue *round_message_queue_new(void)
{
  RoundMessageQueue *queue;

  queue = (RoundMessageQueue *)malloc(sizeof(RoundMessageQueue));

  if (!queue)
    return NULL;

  round_list_header_init((RoundList *)queue);
  queue->userData = NULL;

  return queue;
}

/****************************************
* round_message_queue_delete
****************************************/

void round_message_queue_delete(RoundMessageQueue *queue)
{
  if (!queue)
    return;
  
  round_message_queue_clear(queue);
  
  free(queue);
}
