/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_CLOCK_H_
#define _ROUND_CLOCK_H_

#include <time.h>

#include <round/typedef.h>
#include <round/util/mutex.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define ROUND_CLOCK_INITIAL_VALUE 0
#define ROUND_CLOCK_INCREMENT_VALUE 1
  
/****************************************
 * Constant
 ****************************************/

typedef enum {
  RoundClockOrderSame = 0,
  RoundClockOrderDescending = -1,
  RoundClockOrderAscending = 1,
} RoundClockOrder;

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  RoundMutex *mutex;
  clock_t value;
} RoundClock;

/****************************************
* Function
****************************************/

RoundClock *round_clock_new(void);
bool round_clock_delete(RoundClock *clk);
bool round_clock_clear(RoundClock *clk);

bool round_clock_setvalue(RoundClock *clk, clock_t value);
bool round_clock_setremotevalue(RoundClock *clk, clock_t value);
clock_t round_clock_getvalue(RoundClock *clk);
clock_t round_clock_increment(RoundClock *clk);
RoundClockOrder round_clock_compare(RoundClock *clk1, RoundClock *clk2);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
