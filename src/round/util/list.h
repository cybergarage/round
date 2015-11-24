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

typedef int (*ROUND_ORDERED_LIST_COMPAREFUNC)(void *, void *);
typedef ROUND_LIST_DESTRUCTORFUNC ROUND_ORDERED_LIST_DESTRUCTORFUNC;

enum {
  RoundListNodeCompareSame = 0,
  RoundListNodeCompareLess = -1,
  RoundListNodeCompareGreater = 1,
};
  
/****************************************
 * Data Type
 ****************************************/

#define ROUND_LIST_STRUCT_MEMBERS \
  bool headFlag; \
  struct _RoundList *prev; \
  struct _RoundList *next;
  
typedef struct _RoundList {
  ROUND_LIST_STRUCT_MEMBERS
} RoundList, RoundListNode;

typedef struct {
  RoundList *sortedList;
  ROUND_ORDERED_LIST_COMPAREFUNC cmpFunc;
  ROUND_ORDERED_LIST_DESTRUCTORFUNC dstructorFunc;
} RoundOrderedList;

/****************************************
 * Functions
 ****************************************/

RoundList *round_list_new();
RoundListNode *round_list_node_new();
  
bool round_list_header_init(RoundList *list);
bool round_list_node_init(RoundListNode *list);

bool round_list_insert(RoundListNode *prevNode, RoundListNode *node);

bool round_list_add(RoundList *list, RoundListNode *node);
bool round_list_addfirst(RoundList *list, RoundListNode *node);
bool round_list_addlast(RoundList *list, RoundListNode *node);
#define round_list_add(list,node) round_list_addlast(list,node)

bool round_list_remove(RoundListNode *node);

size_t round_list_size(RoundList *list);

RoundListNode *round_list_get(RoundList *list, size_t index);
RoundListNode *round_list_getfirst(RoundList *list);
RoundListNode *round_list_getlast(RoundList *list);
#define round_list_gets(list) round_list_getfirst(list)

RoundListNode *round_list_prev_circular(RoundListNode *node);
RoundListNode *round_list_prev(RoundListNode *node);
RoundListNode *round_list_next_circular(RoundListNode *node);
RoundListNode *round_list_next(RoundListNode *node);

bool round_list_clear(RoundList *list, ROUND_LIST_DESTRUCTORFUNC dstructorFunc);
bool round_list_delete(RoundList *list);
bool round_list_node_delete(RoundList *node);

/****************************************
 * Functions
 ****************************************/

RoundOrderedList *round_ordered_list_new();
bool round_ordered_list_delete(RoundOrderedList *list);
bool round_ordered_list_clear(RoundOrderedList *list);

#define round_ordered_list_setcmpfunc(list,func) (list->cmpFunc = (ROUND_ORDERED_LIST_COMPAREFUNC)func)
#define round_ordered_list_setdestructorfunc(list,func) (list->dstructorFunc = (ROUND_ORDERED_LIST_DESTRUCTORFUNC)func)
  
bool round_ordered_list_add(RoundOrderedList *list, RoundListNode *node);

#define round_ordered_list_remove(node) round_list_remove((RoundListNode *)node)
#define round_ordered_list_size(list) round_list_size(list->sortedList)
  
#define round_ordered_list_gets(list) round_list_gets(list->sortedList)
#define round_ordered_list_get(list,index) round_list_get(list->sortedList,index)
#define round_ordered_list_getlast(list) round_list_getlast(list->sortedList)
  
#define round_ordered_list_prev_circular(node) round_list_prev_circular(node)
#define round_ordered_list_prev(node) round_list_prev(node)
#define round_ordered_list_next_circular(node) round_list_next_circular(node)
#define round_ordered_list_next(node) round_list_next(node)
  
#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
