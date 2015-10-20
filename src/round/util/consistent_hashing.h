/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_CONSISTENT_HASHING_H_
#define _ROUNDC_UTIL_CONSISTENT_HASHING_H_

#include <round/typedef.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef RoundOrderedList RoundConsistentHashingRing;

/****************************************
 * Functions
 ****************************************/

#define round_consistenthashing_ring_new() round_ordered_list_new()
#define round_consistenthashing_ring_delete(ring) round_ordered_list_delete(ring)

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
