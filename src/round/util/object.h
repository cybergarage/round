/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_UTIL_OBJECT_H_
#define _ROUND_UTIL_OBJECT_H_

#include <round/typedef.h>
#include <round/util/mutex.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

#define ROUND_OBJECT_STRUCT_MEMBERS \
  RoundMutex *mutex; \
  size_t refCnt;
  
typedef struct _RoundObject {
  ROUND_OBJECT_STRUCT_MEMBERS
} RoundObject;

/****************************************
 * Functions
 ****************************************/

RoundObject *round_object_new();
bool round_object_init(RoundObject *obj);
bool round_object_delete(RoundObject *obj);

bool round_object_alloc(RoundObject *obj);
bool round_object_release(RoundObject *obj);

#define round_object_getreferencecount(obj) (obj->refCnt)
#define round_object_hasreference(obj) ((obj->refCnt > 0) ? true : false)

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif
