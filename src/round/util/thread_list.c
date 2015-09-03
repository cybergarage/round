/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/thread.h>

/****************************************
* round_threadlist_new
****************************************/

RoundThreadList *round_threadlist_new(void)
{
  RoundThreadList *threadList;

  threadList = (RoundThreadList *)malloc(sizeof(RoundThreadList));

  if (!threadList)
    return NULL;

  round_list_header_init((RoundList *)threadList);
  threadList->runnableFlag = false;
  threadList->action = NULL;
  threadList->userData = NULL;

  return threadList;
}

/****************************************
* round_threadlist_delete
****************************************/

void round_threadlist_delete(RoundThreadList *threadList)
{
  if (!threadList)
    return;
  
  round_threadlist_clear(threadList);
  free(threadList);
}

/****************************************
* round_threadlist_start
****************************************/

bool round_threadlist_start(RoundThreadList *threadList)
{
  RoundThreadList *thread;

  if (!threadList)
    return false;
  
  for (thread = round_threadlist_gets(threadList); thread != NULL; thread = round_thread_next(thread)) {
    round_thread_start(thread);
  }

  return true;
}

/****************************************
* round_threadlist_stop
****************************************/

bool round_threadlist_stop(RoundThreadList *threadList)
{
  RoundThreadList *thread;
  
  if (!threadList)
    return false;
  
  for (thread = round_threadlist_gets(threadList); thread != NULL; thread = round_thread_next(thread))
    round_thread_stop(thread);

  return true;
}
