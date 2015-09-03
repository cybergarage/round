/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UECHO_UTIL_THREAD_H_
#define _UECHO_UTIL_THREAD_H_

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

#define UECHO_THREAD_MIN_SLEEP 1000

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundThread {
  bool headFlag;
  struct _RoundThread *prev;
  struct _RoundThread *next;
    
  bool runnableFlag;

#if defined(WIN32)
  HANDLE hThread;
  DWORD threadID;
#else
  pthread_t pThread;
#endif

  void (*action)(struct _RoundThread *);
  void *userData;
} RoundThread, RoundThreadList;

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

RoundThreadList *round_threadlist_new();
void round_threadlist_delete(RoundThreadList *threadList);

#define round_threadlist_clear(threadList) round_list_clear((RoundList *)threadList, (UECHO_LIST_DESTRUCTORFUNC)round_thread_delete)
#define round_threadlist_size(threadList) round_list_size((RoundList *)threadList)
#define round_threadlist_gets(threadList) (RoundThread *)round_list_next((RoundList *)threadList)
#define round_threadlist_add(threadList, thread) round_list_add((RoundList *)threadList, (RoundList *)thread)
#define round_threadlist_remove(thread) round_list_remove((RoundList *)thread)

bool round_threadlist_start(RoundThreadList *threadList);
bool round_threadlist_stop(RoundThreadList *threadList);

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
