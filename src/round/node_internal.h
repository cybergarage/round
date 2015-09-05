/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_NODE_INTERNAL_H_
#define _ROUNDC_NODE_INTERNAL_H_

#include <round/typedef.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundNode {
  bool headFlag;
  struct _RoundNode *prev;
  struct _RoundNode *next;
} RoundNode, RoundNodeList;

/****************************************
 * Public Header
 ****************************************/
  
#include <round/node.h>
  
/****************************************
 * Function
 ****************************************/

#define round_node_remove(node) round_list_remove((RoundList *)node)

/****************************************
 * Function (Node List)
 ****************************************/
  
RoundNodeList *round_nodelist_new(void);
void round_nodelist_delete(RoundNodeList *nodes);
  
#define round_nodelist_clear(nodes) round_list_clear((RoundList *)nodes, (ROUND_LIST_DESTRUCTORFUNC)round_node_delete)
#define round_nodelist_size(nodes) round_list_size((RoundList *)nodes)
#define round_nodelist_gets(nodes) (RoundNode *)round_list_next((RoundList *)nodes)
#define round_nodelist_add(nodes,node) round_list_add((RoundList *)nodes, (RoundList *)node)

#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUNDC_NODE_INTERNAL_H_ */
