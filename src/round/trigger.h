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

typedef struct {
  RoundThread *thread;
} RoundTrigger;

typedef struct {
  RoundThreadManager *threadMgr;
} RoundTriggerManager;

/****************************************
 * Function
 ****************************************/
  
RoundTrigger *round_trigger_new();
bool round_trigger_clear(RoundTrigger *trigger);
bool round_trigger_delete(RoundTrigger *trigger);

/****************************************
 * Function (Manager)
 ****************************************/
  
RoundTriggerManager *round_trigger_manager_new();
bool round_trigger_manager_delete(RoundTriggerManager *mgr);
  
#ifdef  __cplusplus
}
#endif

#endif
