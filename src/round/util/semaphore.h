/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_SEMAPHORE_H_
#define _ROUND_UTIL_SEMAPHORE_H_

#include <round/typedef.h>
#include <time.h>

#if defined(__APPLE__)
#include <mach/mach.h>
#include <mach/semaphore.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Types
 ****************************************/

#if defined(__APPLE__)
  typedef semaphore_t SemaphoreId;
#else
  typedef sem_t SemaphoreId;
#endif
  
typedef struct {
  SemaphoreId semId;
  bool isInitialized;
  size_t maxCnt;
} RoundSemaphore;

/****************************************
 * Functions
 ****************************************/

RoundSemaphore *round_semaphore_new(size_t max);
bool round_semaphore_delete(RoundSemaphore *sem);

bool round_semaphore_post(RoundSemaphore *sem);
bool round_semaphore_reset(RoundSemaphore *sem);
bool round_semaphore_wait(RoundSemaphore *sem);
bool round_semaphore_timedwait(RoundSemaphore *sem, time_t timeoutSec);
bool round_semaphore_cancel(RoundSemaphore *sem);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
