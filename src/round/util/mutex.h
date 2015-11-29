/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_MUTEX_H_
#define _ROUND_UTIL_MUTEX_H_

#include <round/typedef.h>

#if defined(WIN32)
#include <winsock2.h>
#else
#include <pthread.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Types
 ****************************************/

typedef struct {
#if defined(WIN32)
  HANDLE  mutexID;
#else
  pthread_mutex_t mutexID;
#endif
} RoundMutex;

/****************************************
 * Functions
 ****************************************/

RoundMutex *round_mutex_new(void);
bool round_mutex_delete(RoundMutex *mutex);

bool round_mutex_lock(RoundMutex *mutex);
bool round_mutex_unlock(RoundMutex *mutex);

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
