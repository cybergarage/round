/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/semaphore.h>

bool round_semaphore_init(RoundSemaphore* sem, size_t maxCnt);
bool round_semaphore_destory(RoundSemaphore* sem);

/****************************************
* round_semaphore_new
****************************************/

RoundSemaphore* round_semaphore_new(size_t maxCnt)
{
  RoundSemaphore* sem;

  sem = (RoundSemaphore*)malloc(sizeof(RoundSemaphore));

  if (!sem)
    return NULL;

  sem->isInitialized = false;
  sem->maxCnt = maxCnt;

  if (!round_semaphore_init(sem, maxCnt)) {
    round_semaphore_delete(sem);
    return NULL;
  }

  return sem;
}

/****************************************
* round_semaphore_delete
****************************************/

bool round_semaphore_delete(RoundSemaphore* sem)
{
  if (!sem)
    return false;

  round_semaphore_destory(sem);
  free(sem);

  return true;
}

/****************************************
 * round_semaphore_init
 ****************************************/

bool round_semaphore_init(RoundSemaphore* sem, size_t maxCnt)
{
  if (!sem)
    return false;

  if (sem->isInitialized)
    return true;

#if defined(__APPLE__)
  sem->isInitialized = (semaphore_create(mach_task_self(), &sem->semId, SYNC_POLICY_FIFO, (int)maxCnt)
                           == KERN_SUCCESS)
      ? true
      : false;
#else
  sem->isInitialized = (sem_init(&sem->semId, 0, maxCnt) == 0) ? true : false;
#endif

  return sem->isInitialized;
}

/****************************************
 * round_semaphore_destory
 ****************************************/

bool round_semaphore_destory(RoundSemaphore* sem)
{
  if (!sem)
    return false;

  if (!sem->isInitialized)
    return true;

#if defined(__APPLE__)
  sem->isInitialized = (semaphore_destroy(mach_task_self(), sem->semId) == KERN_SUCCESS) ? false
                                                                                         : true;
#else
  sem->isInitialized = (sem_destroy(&sem->semId) == 0) ? false : true;
#endif

  return !sem->isInitialized;
}

/****************************************
 * round_semaphore_post
 ****************************************/

bool round_semaphore_post(RoundSemaphore* sem)
{
  bool isSuccess;

  if (!sem)
    return false;

  if (!sem->isInitialized)
    return false;

  isSuccess = true;

#if defined(__APPLE__)
  isSuccess = (semaphore_signal(sem->semId) == KERN_SUCCESS) ? true : false;
#else
  isSuccess = (sem_post(&sem->semId) == 0) ? true : false;
#endif

  return isSuccess;
}

/****************************************
 * round_semaphore_timedwait
 ****************************************/

bool round_semaphore_timedwait(RoundSemaphore* sem, time_t timeoutSec)
{
  bool isSuccess;

  if (!sem)
    return false;

  if (!sem->isInitialized)
    return false;

  isSuccess = true;

#if defined(__APPLE__)
  if (0 < timeoutSec) {
    mach_timespec_t machTimeout;
    machTimeout.tv_sec = (unsigned int)timeoutSec;
    machTimeout.tv_nsec = 0;
    isSuccess = (semaphore_timedwait(sem->semId, machTimeout) == KERN_SUCCESS)
        ? true
        : false;
  }
  else {
    isSuccess = (semaphore_wait(sem->semId) == KERN_SUCCESS) ? true : false;
  }
#else
  if (0 < timeoutSec) {
    struct timespec absTimeout;
    absTimeout.tv_sec = timeoutSec;
    absTimeout.tv_nsec = 0;
    isSuccess = (sem_timedwait(&sem->semId, &absTimeout) == 0) ? true : false;
  }
  else {
    isSuccess = (sem_wait(&sem->semId) == 0) ? true : false;
  }
#endif

  return isSuccess;
}

/****************************************
 * round_semaphore_timedwait
 ****************************************/

bool round_semaphore_wait(RoundSemaphore* sem)
{
  return round_semaphore_timedwait(sem, 0);
}

/****************************************
 * round_semaphore_timedwait
 ****************************************/

bool round_semaphore_reset(RoundSemaphore* sem)
{
  if (!round_semaphore_destory(sem))
    return false;
  return round_semaphore_init(sem, sem->maxCnt);
}

/****************************************
 * round_semaphore_cancel
 ****************************************/

bool round_semaphore_cancel(RoundSemaphore* sem)
{
  return round_semaphore_destory(sem);
}
