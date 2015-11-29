/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_THREAD_H_
#define _ROUND_UTIL_THREAD_H_

#include <round/typedef.h>
#include <round/util/list.h>

#if defined(WIN32)
#include <windows.h>
#else
#include <pthread.h>
#include <signal.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Define
 ****************************************/

#define ROUND_THREAD_MIN_SLEEP 1000

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundThread {
  ROUND_LIST_STRUCT_MEMBERS
  
  bool runnableFlag;

#if defined(WIN32)
  HANDLE hThread;
  DWORD threadID;
#else
  pthread_t pThread;
#endif

  void (*action)(struct _RoundThread *);
  void *userData;
} RoundThread, RoundThreadManager;

typedef void (*RoundThreadFunc)(RoundThread *);

/****************************************
* Function
****************************************/

RoundThread *round_thread_new(void);
bool round_thread_delete(RoundThread *thread);

bool round_thread_start(RoundThread *thread);
bool round_thread_stop(RoundThread *thread);
bool round_thread_restart(RoundThread *thread);
bool round_thread_isrunnable(RoundThread *thread);
bool round_thread_isrunning(RoundThread *thread);
  
void round_thread_setaction(RoundThread *thread, RoundThreadFunc actionFunc);
void round_thread_setuserdata(RoundThread *thread, void *data);
void *round_thread_getuserdata(RoundThread *thread);

#define round_thread_next(thread) (RoundThread *)round_list_next((RoundList *)thread)
#define round_thread_remove(thread) round_list_remove((RoundList *)thread)

/****************************************
* Function (Thread List)
****************************************/

RoundThreadManager *round_thread_manager_new();
void round_thread_manager_delete(RoundThreadManager *threadMgr);

#define round_thread_manager_clear(threadMgr) round_list_clear((RoundList *)threadMgr, (ROUND_LIST_DESTRUCTORFUNC)round_thread_delete)
#define round_thread_manager_size(threadMgr) round_list_size((RoundList *)threadMgr)
#define round_thread_manager_gets(threadMgr) (RoundThread *)round_list_next((RoundList *)threadMgr)
#define round_thread_manager_add(threadMgr, thread) round_list_add((RoundList *)threadMgr, (RoundList *)thread)
#define round_thread_manager_remove(thread) round_list_remove((RoundList *)thread)

bool round_thread_manager_start(RoundThreadManager *threadMgr);
bool round_thread_manager_stop(RoundThreadManager *threadMgr);
bool round_thread_manager_isrunning(RoundThreadManager *threadMgr);

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
