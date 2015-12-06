/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#if !defined(WIN32)
#include <signal.h>
#endif

#include <round/clock.h>
#include <string.h>

/****************************************
* round_clock_new
****************************************/

RoundClock* round_clock_new(void)
{
  RoundClock* clk;

  clk = (RoundClock*)malloc(sizeof(RoundClock));

  if (!clk)
    return NULL;

  clk->mutex = round_mutex_new();

  round_clock_clear(clk);

  return clk;
}

/****************************************
* round_clock_delete
****************************************/

bool round_clock_delete(RoundClock* clk)
{
  if (!clk)
    return false;

  round_mutex_delete(clk->mutex);

  free(clk);

  return true;
}

/****************************************
 * round_clock_clear
 ****************************************/

bool round_clock_clear(RoundClock* clk)
{
  if (!clk)
    return false;

  clk->value = ROUND_CLOCK_INITIAL_VALUE;

  return true;
}

/****************************************
 * round_clock_setvalue
 ****************************************/

bool round_clock_setvalue(RoundClock* clk, clock_t value)
{
  if (!clk)
    return false;

  round_mutex_lock(clk->mutex);

  clk->value = value;

  round_mutex_unlock(clk->mutex);

  return true;
}

/****************************************
 * round_clock_setvalue
 ****************************************/

bool round_clock_setremotevalue(RoundClock* clk, clock_t remoteValue)
{
  if (!clk)
    return 0;

  round_mutex_lock(clk->mutex);

  if (clk->value < remoteValue) {
    clk->value = remoteValue;
  }
  clk->value += ROUND_CLOCK_INCREMENT_VALUE;

  round_mutex_unlock(clk->mutex);

  return true;
}

/****************************************
 * round_clock_getvalue
 ****************************************/

clock_t round_clock_getvalue(RoundClock* clk)
{
  clock_t lastValue;

  if (!clk)
    return 0;

  round_mutex_lock(clk->mutex);

  lastValue = clk->value;

  round_mutex_unlock(clk->mutex);

  return lastValue;
}

/****************************************
 * round_clock_increment
 ****************************************/

clock_t round_clock_increment(RoundClock* clk)
{
  clock_t lastValue;

  if (!clk)
    return true;

  round_mutex_lock(clk->mutex);

  clk->value += ROUND_CLOCK_INCREMENT_VALUE;
  lastValue = clk->value;

  round_mutex_unlock(clk->mutex);

  return lastValue;
}

/****************************************
 * round_clock_compare
 ****************************************/

RoundClockOrder round_clock_compare(RoundClock* clk1, RoundClock* clk2)
{
  if (clk1->value == clk2->value)
    return RoundClockOrderSame;
  return (clk2->value < clk1->value) ? RoundClockOrderDescending : RoundClockOrderAscending;
}
