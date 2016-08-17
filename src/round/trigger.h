/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_TRIGGER_H_
#define _ROUND_TRIGGER_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <round/util/thread.h>

#ifdef  __cplusplus
extern "C" {
#endif
  
/****************************************
 * Data Type
 ****************************************/

typedef RoundThread RoundTrigger;
typedef RoundThreadFunc RoundTriggerFunc;

typedef struct {
  RoundThreadManager *threadMgr;
} RoundTriggerManager;

/****************************************
 * Function
 ****************************************/
  
#define round_trigger_new round_thread_new
#define round_trigger_delete(trigger) round_thread_delete(trigger)

#define round_trigger_setname(trigger,value) round_thread_setname(trigger,value)
#define round_trigger_getname(trigger) round_thread_getname(trigger)
#define round_trigger_hasname(trigger) round_thread_hasname(trigger)
#define round_trigger_isname(trigger,value) round_thread_isname(trigger,value)

#define round_trigger_setaction(trigger,func) round_thread_setaction(trigger,func)
  
#define round_trigger_setloop(thread,flag) round_thread_setloop(thread,flag)
#define round_trigger_isloop(thread) round_thread_isloop(thread)
  
#define round_trigger_setcycleinterval(thread,value) round_thread_setcycleinterval(thread,value)
#define round_trigger_getcycleinterval(thread) round_thread_getcycleinterval(thread)

#define round_trigger_setstarttime(thread,value) round_thread_setstarttime(thread,value)
#define round_trigger_getstarttime(thread) round_thread_getstarttime(thread)
#define round_trigger_isstarttimeenabled(thread) round_thread_isstarttimeenabled(thread)
  
#define round_trigger_setstoptime(thread,value) round_thread_setstoptime(thread,value)
#define round_trigger_getstoptime(thread) round_thread_getstoptime(thread)
#define round_trigger_isstoptimeenabled(thread) round_thread_isstoptimeenabled(thread)

/****************************************
 * Function (Manager)
 ****************************************/
  
RoundTriggerManager *round_trigger_manager_new();
bool round_trigger_manager_delete(RoundTriggerManager *mgr);
  
#ifdef  __cplusplus
}
#endif

#endif
