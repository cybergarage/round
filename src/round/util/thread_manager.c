/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/thread.h>

/****************************************
* round_thread_manager_new
****************************************/

RoundThreadManager *round_thread_manager_new(void)
{
  RoundThreadManager *threadMgr;

  threadMgr = (RoundThreadManager *)malloc(sizeof(RoundThreadManager));

  if (!threadMgr)
    return NULL;

  round_list_header_init((RoundList *)threadMgr);
  threadMgr->runnableFlag = false;
  threadMgr->action = NULL;
  threadMgr->userData = NULL;

  return threadMgr;
}

/****************************************
* round_thread_manager_delete
****************************************/

void round_thread_manager_delete(RoundThreadManager *threadMgr)
{
  if (!threadMgr)
    return;
  
  round_thread_manager_clear(threadMgr);
  free(threadMgr);
}

/****************************************
* round_thread_manager_start
****************************************/

bool round_thread_manager_start(RoundThreadManager *threadMgr)
{
  RoundThreadManager *thread;

  if (!threadMgr)
    return false;
  
  for (thread = round_thread_manager_gets(threadMgr); thread != NULL; thread = round_thread_next(thread)) {
    round_thread_start(thread);
  }

  return true;
}

/****************************************
* round_thread_manager_stop
****************************************/

bool round_thread_manager_stop(RoundThreadManager *threadMgr)
{
  RoundThreadManager *thread;
  
  if (!threadMgr)
    return false;
  
  for (thread = round_thread_manager_gets(threadMgr); thread != NULL; thread = round_thread_next(thread))
    round_thread_stop(thread);

  return true;
}
