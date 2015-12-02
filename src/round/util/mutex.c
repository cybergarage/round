/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/mutex.h>

#include <errno.h>

/****************************************
* round_mutex_new
****************************************/

RoundMutex* round_mutex_new(void)
{
  RoundMutex* mutex;

  mutex = (RoundMutex*)malloc(sizeof(RoundMutex));

  if (!mutex)
    return NULL;

#if defined(WIN32)
  mutex->mutexID = CreateMutex(NULL, false, NULL);
#else
  pthread_mutex_init(&mutex->mutexID, NULL);
#endif

  return mutex;
}

/****************************************
* round_mutex_delete
****************************************/

bool round_mutex_delete(RoundMutex* mutex)
{
  if (!mutex)
    return false;

#if defined(WIN32)
  CloseHandle(mutex->mutexID);
#else
  pthread_mutex_destroy(&mutex->mutexID);
#endif
  free(mutex);

  return true;
}

/****************************************
* round_mutex_lock
****************************************/

bool round_mutex_lock(RoundMutex* mutex)
{
  if (!mutex)
    return false;

#if defined(WIN32)
  WaitForSingleObject(mutex->mutexID, INFINITE);
#else
  pthread_mutex_lock(&mutex->mutexID);
#endif

  return true;
}

/****************************************
* round_mutex_unlock
****************************************/

bool round_mutex_unlock(RoundMutex* mutex)
{
  if (!mutex)
    return false;

#if defined(WIN32)
  ReleaseMutex(mutex->mutexID);
#else
  pthread_mutex_unlock(&mutex->mutexID);
#endif
  return true;
}
