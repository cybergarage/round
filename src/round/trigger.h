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
#include <round/util/map.h>

#ifdef  __cplusplus
extern "C" {
#endif
  
/****************************************
 * Data Type
 ****************************************/

typedef RoundThread RoundTrigger;
typedef RoundThreadFunc RoundTriggerFunc;
typedef RoundThreadManager RoundTriggerManager;

/****************************************
 * Function
 ****************************************/
  
RoundTrigger *round_trigger_new(void);
  
#define round_trigger_delete(trigger) round_thread_delete(trigger)

#define round_trigger_setname(trigger,value) round_thread_setname(trigger,value)
#define round_trigger_getname(trigger) round_thread_getname(trigger)
#define round_trigger_hasname(trigger) round_thread_hasname(trigger)
#define round_trigger_isname(trigger,value) round_thread_isname(trigger,value)

#define round_trigger_setaction(trigger,func) round_thread_setaction(trigger,func)
  
#define round_trigger_setloop(trigger,flag) round_thread_setloop(trigger,flag)
#define round_trigger_isloop(trigger) round_thread_isloop(trigger)
  
#define round_trigger_setcycleinterval(trigger,value) round_thread_setcycleinterval(trigger,value)
#define round_trigger_getcycleinterval(trigger) round_thread_getcycleinterval(trigger)

#define round_trigger_setstarttime(trigger,value) round_thread_setstarttime(trigger,value)
#define round_trigger_getstarttime(trigger) round_thread_getstarttime(trigger)
#define round_trigger_isstarttimeenabled(trigger) round_thread_isstarttimeenabled(trigger)
  
#define round_trigger_setstoptime(trigger,value) round_thread_setstoptime(trigger,value)
#define round_trigger_getstoptime(trigger) round_thread_getstoptime(trigger)
#define round_trigger_isstoptimeenabled(trigger) round_thread_isstoptimeenabled(trigger)

#define round_trigger_setroutemanager(mgr,data) round_thread_setuserdata(mgr,data)
#define round_trigger_getroutemanager(mgr) ((RoundRouteManager *)round_thread_getuserdata(mgr))

/****************************************
 * Function (Manager)
 ****************************************/
  
#define round_trigger_manager_new(mgr) round_thread_manager_new(mgr)
#define round_trigger_manager_delete(mgr) round_thread_manager_delete(mgr)

#define round_trigger_manager_size(mgr) round_thread_manager_size(mgr)
  
bool round_trigger_manager_settrigger(RoundTriggerManager *mgr, RoundTrigger *trigger);

#define round_trigger_manager_start(mgr) round_thread_manager_start(mgr)
#define round_trigger_manager_stop(mgr) round_thread_manager_start(mgr)
#define round_trigger_manager_isrunning(mgr) round_thread_manager_start(mgr)

#define round_trigger_manager_hastriggerbyname(mgr,name) round_thread_manager_hasthreadbyname(mgr, name)
#define round_trigger_manager_removetriggerbyname(mgr,name) round_thread_manager_removethreadbyname(mgr, name)
#define round_trigger_manager_gettriggerbyname(mgr,name) round_thread_manager_getthreadbyname(mgr, name)

#define round_trigger_manager_setroutemanager(mgr,data) round_thread_manager_setuserdata(mgr,data)
#define round_trigger_manager_getroutemanager(mgr) ((RoundRouteManager *)round_thread_manager_getuserdata(mgr))

#ifdef  __cplusplus
}
#endif

#endif
