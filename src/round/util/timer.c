/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/timer.h>

#include <limits.h>

#if defined(WIN32)
#include <windows.h>
#include <time.h>
#else
#include <unistd.h>
#include <time.h>
#endif

/****************************************
* round_wait
****************************************/

void round_wait(clock_t mtime)
{
#if defined(WIN32)
  Sleep(mtime);
#else
  usleep(((useconds_t)(mtime * 1000)));
#endif
}

/****************************************
* round_waitrandom
****************************************/

void round_waitrandom(clock_t mtime)
{
  double factor;
  long waitTime;

  factor = (double)rand() / (double)RAND_MAX;
  waitTime = (long)((double)mtime * factor);
  round_wait(waitTime);
}

/****************************************
* round_getcurrentsystemtime
****************************************/

clock_t round_getcurrentsystemtime(void)
{
  return (size_t)(time((time_t *)NULL));
}

/****************************************
* round_random
****************************************/

float round_random(void)
{
  static bool seedDone = false;

  if (seedDone == false) {
    srand((int)(round_getcurrentsystemtime() % INT_MAX));
    seedDone = true;
  }
  
  return (float)rand() / (float)RAND_MAX;
}
