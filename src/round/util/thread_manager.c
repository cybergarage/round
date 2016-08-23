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

RoundThreadManager* round_thread_manager_new(void)
{
  RoundThreadManager* mgr = (RoundThreadManager*)malloc(sizeof(RoundThreadManager));

  if (!mgr)
    return NULL;

  round_list_header_init((RoundList*)mgr);
  
  mgr->runnableFlag = false;
  mgr->action = NULL;
  mgr->userData = NULL;

  return mgr;
}

/****************************************
* round_thread_manager_delete
****************************************/

bool round_thread_manager_delete(RoundThreadManager* mgr)
{
  if (!mgr)
    return false;

  if (!round_thread_manager_clear(mgr))
    return false;

  free(mgr);
  
  return true;
}

/****************************************
* round_thread_manager_start
****************************************/

bool round_thread_manager_start(RoundThreadManager* mgr)
{
  if (!mgr)
    return false;

  RoundThreadManager* thread;
  for (thread = round_thread_manager_gets(mgr); thread != NULL; thread = round_thread_next(thread)) {
    round_thread_start(thread);
  }

  return true;
}

/****************************************
* round_thread_manager_stop
****************************************/

bool round_thread_manager_stop(RoundThreadManager* mgr)
{
  if (!mgr)
    return false;

  RoundThreadManager* thread;
  for (thread = round_thread_manager_gets(mgr); thread != NULL; thread = round_thread_next(thread)) {
    round_thread_stop(thread);
  }

  return true;
}

/****************************************
 * round_thread_manager_isrunning
 ****************************************/

bool round_thread_manager_isrunning(RoundThreadManager* mgr)
{
  RoundThreadManager* thread;
  for (thread = round_thread_manager_gets(mgr); thread != NULL; thread = round_thread_next(thread)) {
    if (!round_thread_isrunning(thread))
      return false;
  }

  return true;
}

/****************************************
 * round_thread_manager_getthreadbyname
 ****************************************/

RoundThread *round_thread_manager_getthreadbyname(RoundThreadManager *mgr, const char *name)
{
  if (!mgr)
    return NULL;
  
  RoundThreadManager* thread;
  for (thread = round_thread_manager_gets(mgr); thread != NULL; thread = round_thread_next(thread)) {
    if (!round_thread_isname(thread, name))
      return thread;
  }
  
  return NULL;
}

/****************************************
 * round_thread_manager_removethreadbyname
 ****************************************/

bool round_thread_manager_removethreadbyname(RoundThreadManager *mgr, const char *name)
{
  if (!mgr)
    return NULL;

  RoundThreadManager *thread = round_thread_manager_getthreadbyname(mgr, name);
  if (!thread)
    return NULL;

  return round_thread_remove(thread);
}
