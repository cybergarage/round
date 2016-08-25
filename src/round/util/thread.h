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
#include <round/util/strings.h>

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

#define ROUND_THREAD_MIN_SLEEP 0.1

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundThread {
  ROUND_LIST_STRUCT_MEMBERS
  
  RoundString *name;
  
  bool runnableFlag;
  bool runningFlag;

#if defined(WIN32)
  HANDLE hThread;
  DWORD threadID;
#else
  pthread_t pThread;
#endif

  bool isLoop;
  double cycleInterval;
  double startTime;
  double stopTime;

  void (*action)(struct _RoundThread *);

  void *userData;
} RoundThread, RoundThreadManager;

typedef void (*RoundThreadFunc)(RoundThread *);

/****************************************
* Function
****************************************/

RoundThread *round_thread_new(void);
bool round_thread_delete(RoundThread *thread);

#define round_thread_next(thread) (RoundThread *)round_list_next((RoundList *)thread)
#define round_thread_remove(thread) round_list_remove((RoundList *)thread)
  
bool round_thread_start(RoundThread *thread);
bool round_thread_stop(RoundThread *thread);
bool round_thread_restart(RoundThread *thread);
bool round_thread_isrunnable(RoundThread *thread);
bool round_thread_isrunning(RoundThread *thread);
  
void round_thread_setaction(RoundThread *thread, RoundThreadFunc actionFunc);

#define round_thread_setname(thread,value) round_string_setvalue(thread->name,value)
#define round_thread_getname(thread) round_string_getvalue(thread->name)
#define round_thread_hasname(thread) round_string_hasvalue(thread->name)
#define round_thread_isname(thread,value) round_string_isvalue(thread->name,value)

#define round_thread_setloop(thread,flag) (thread->isLoop = flag)
#define round_thread_isloop(thread) (thread->isLoop)

#define round_thread_setcycleinterval(thread,value) (thread->cycleInterval = value)
#define round_thread_getcycleinterval(thread) (thread->cycleInterval)

#define round_thread_setstarttime(thread,value) (thread->startTime = value)
#define round_thread_getstarttime(thread) (thread->startTime)
#define round_thread_isstarttimeenabled(thread) ((0.0 < thread->startTime) ? true : false)

#define round_thread_setstoptime(thread,value) (thread->stopTime = value)
#define round_thread_getstoptime(thread) (thread->stopTime)
#define round_thread_isstoptimeenabled(thread) ((0.0 < thread->stopTime) ? true : false)

void round_thread_setuserdata(RoundThread *thread, void *data);
void *round_thread_getuserdata(RoundThread *thread);

/****************************************
* Function (Thread List)
****************************************/

RoundThreadManager *round_thread_manager_new();
bool round_thread_manager_delete(RoundThreadManager *mgr);

#define round_thread_manager_clear(mgr) round_list_clear((RoundList *)mgr, (ROUND_LIST_DESTRUCTORFUNC)round_thread_delete)
#define round_thread_manager_size(mgr) round_list_size((RoundList *)mgr)
#define round_thread_manager_gets(mgr) (RoundThread *)round_list_next((RoundList *)mgr)
#define round_thread_manager_add(mgr, thread) round_list_add((RoundList *)mgr, (RoundList *)thread)
#define round_thread_manager_remove(thread) round_list_remove((RoundList *)thread)

#define round_thread_manager_setuserdata(mgr,data) round_thread_setuserdata(mgr,data)
#define round_thread_manager_getuserdata(mgr) round_thread_getuserdata(mgr)
  
bool round_thread_manager_start(RoundThreadManager *mgr);
bool round_thread_manager_stop(RoundThreadManager *mgr);
bool round_thread_manager_isrunning(RoundThreadManager *mgr);

RoundThread *round_thread_manager_getthreadbyname(RoundThreadManager *mgr, const char *name);
bool round_thread_manager_removethreadbyname(RoundThreadManager *mgr, const char *name);
#define round_thread_manager_hasthreadbyname(mgr, name) (round_thread_manager_getthreadbyname(mgr, name) ? true : false)

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
