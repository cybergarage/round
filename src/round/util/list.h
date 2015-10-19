/******************************************************************
 *
 * Round for C
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
typedef int (*ROUND_ORDERED_LIST_COMPAREFUNC)(const void *, const void *);

/****************************************
 * Data Type
 ****************************************/

#define ROUND_LIST_STRUCT_MEMBERS \
  bool headFlag; \
  struct _RoundList *prev; \
  struct _RoundList *next;
  
typedef struct _RoundList {
  ROUND_LIST_STRUCT_MEMBERS
} RoundList;

#define ROUND_ORDERED_LIST_STRUCT_MEMBERS \
  ROUND_LIST_STRUCT_MEMBERS \
  ROUND_ORDERED_LIST_COMPAREFUNC cmpFunc;
  
typedef struct _RoundOrderedList {
  ROUND_ORDERED_LIST_STRUCT_MEMBERS
} RoundOrderedList;

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

/****************************************
 * Functions
 ****************************************/
  
#define round_ordered_list_header_init(list) round_list_header_init(list)
#define round_ordered_list_node_init(list) round_list_node_init(list)

#define round_ordered_list_setcmpfunc(headList,func) (headList->cmpFunc = func)
  
bool round_ordered_list_add(RoundList *headList, RoundList *list);

#define round_ordered_list_remove(list) round_list_remove(list)

#define round_ordered_list_size(headList) round_list_size(headList)
  
#define round_ordered_list_gets(headList) round_list_gets(headList)
#define round_ordered_list_get(headList,index) round_list_get(headList,index)
  
#define round_ordered_list_prev_circular(list) round_list_prev_circular(list)
#define round_ordered_list_prev(list) round_list_prev(list)
#define round_ordered_list_next_circular(list) round_list_next_circular(list)
#define round_ordered_list_next(list) round_list_next(list)
  
#define round_ordered_list_clear(headList, dstructorFunc) round_list_clear(headList, dstructorFunc)

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
