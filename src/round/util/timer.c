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
#include <sys/time.h>
#endif

/****************************************
* round_wait
****************************************/

void round_wait(double waitSec)
{
  if (waitSec < 0.0)
    return;
  
#if defined(WIN32)
  Sleep(waitSec * 1000);
#else
  usleep(((useconds_t)(waitSec * 1000000)));
#endif
}

/****************************************
* round_waitrandom
****************************************/

void round_waitrandom(double waitSec)
{
  double factor = (double)rand() / (double)RAND_MAX;
  round_wait(waitSec * factor);
}

/****************************************
 * round_getcurrentunixtime
 ****************************************/

double round_getcurrentunixtime(void)
{
  double unixTime = 0.0;
  struct timeval now;
  gettimeofday(&now, NULL);
  unixTime = now.tv_sec + (now.tv_usec / 1000000.0);
  return unixTime;
}

/****************************************
* round_getcurrentsystemtime
****************************************/

clock_t round_getcurrentsystemtime(void)
{
  return (size_t)(time((time_t*)NULL));
}

/****************************************
* round_random
****************************************/

double round_random(void)
{
  static bool seedDone = false;

  if (seedDone == false) {
    srand((int)(round_getcurrentsystemtime() % INT_MAX));
    seedDone = true;
  }

  return (double)rand() / (double)RAND_MAX;
}
