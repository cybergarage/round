/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_OBJECT_ORIENTED_H_
#define _ROUND_UTIL_OBJECT_ORIENTED_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef bool (*ROUND_OO_DESCENDANT_DESTORYFUNC)(void *);
  
/****************************************
 * Macros
 ****************************************/

#define ROUND_OO_STRUCT_MEMBERS \
ROUND_OO_DESCENDANT_DESTORYFUNC descDestroyFunc;

#define round_oo_setdescendantdestoroyfunc(obj, func) (obj->descDestroyFunc = (ROUND_OO_DESCENDANT_DESTORYFUNC)func)
#define round_oo_execdescendantdestoroy(obj) ((obj->descDestroyFunc) ? obj->descDestroyFunc(obj) : true)

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif
