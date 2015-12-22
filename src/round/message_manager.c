/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/message.h>

/****************************************
* round_message_manager_new
****************************************/

RoundMessageManager* round_message_manager_new(void)
{
  RoundMessageManager* mgr;

  mgr = (RoundMessageManager*)malloc(sizeof(RoundMessageManager));

  if (!mgr)
    return NULL;

  mgr->queue = round_queue_new();
  mgr->sem = round_semaphore_new(0);
  mgr->mutex = round_mutex_new();

  return mgr;
}

/****************************************
* round_message_manager_delete
****************************************/

bool round_message_manager_delete(RoundMessageManager* mgr)
{
  if (!mgr)
    return false;

  round_message_manager_clear(mgr);

  round_queue_delete(mgr->queue);
  round_semaphore_delete(mgr->sem);
  round_mutex_delete(mgr->mutex);

  free(mgr);

  return true;
}

/****************************************
 * round_message_manager_clear
 ****************************************/

bool round_message_manager_clear(RoundMessageManager* mgr)
{
  RoundMessage* msg;

  if (!mgr)
    return false;

  // TODO : Serialize none executed message
  while (round_queue_pop(mgr->queue, (RoundQueueObject**)&msg)) {
    if (!msg)
      continue;
    round_message_delete(msg);
  }

  round_semaphore_reset(mgr->sem);

  return true;
}

/****************************************
 * round_message_manager_pushmessage
 ****************************************/

bool round_message_manager_pushmessage(RoundMessageManager* mgr, RoundMessage* msg)
{
  if (!mgr)
    return false;

  round_mutex_lock(mgr->mutex);
  round_queue_push(mgr->queue, (RoundQueueObject*)msg);
  round_mutex_unlock(mgr->mutex);

  round_semaphore_post(mgr->sem);

  return true;
}

/****************************************
 * round_message_manager_waitmessage
 ****************************************/

bool round_message_manager_waitmessage(RoundMessageManager* mgr, RoundMessage** msg)
{
  bool isSuccess;

  if (!mgr)
    return false;

  *msg = NULL;
  if (!round_semaphore_wait(mgr->sem))
    return false;

  round_mutex_lock(mgr->mutex);
  isSuccess = round_queue_pop(mgr->queue, (RoundQueueObject**)msg);
  round_mutex_unlock(mgr->mutex);

  return isSuccess;
}
