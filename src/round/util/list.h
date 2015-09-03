/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_LIST_H_
#define _ROUNDC_UTIL_LIST_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Define
 ****************************************/

typedef void (*ROUND_LIST_DESTRUCTORFUNC)(void *);

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundList {
  bool headFlag;
  struct _RoundList *prev;
  struct _RoundList *next;
} RoundList;

/****************************************
 * Functions
 ****************************************/

bool round_list_header_init(RoundList *list);
bool round_list_node_init(RoundList *list);

bool round_list_insert(RoundList *prevList, RoundList *list);
bool round_list_add(RoundList *headList, RoundList *list);
bool round_list_remove(RoundList *list);

size_t round_list_size(RoundList *headList);

RoundList *round_list_gets(RoundList *headList);
RoundList *round_list_get(RoundList *headList, int index);

RoundList *round_list_prev_circular(RoundList *list);
RoundList *round_list_prev(RoundList *list);
RoundList *round_list_next_circular(RoundList *list);
RoundList *round_list_next(RoundList *list);

bool round_list_clear(RoundList *headList, ROUND_LIST_DESTRUCTORFUNC dstructorFunc);

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
