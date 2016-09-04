/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/object.h>
#include <round/util/timer.h>

/****************************************
 * round_object_obj_init
 ****************************************/

RoundObject* round_object_new()
{
  RoundObject* obj = (RoundObject*)malloc(sizeof(RoundObject));
  if (!obj)
    return NULL;

  if (!round_object_init(obj)) {
    round_object_delete(obj);
    return NULL;
  }

  return obj;
}

/****************************************
 * round_object_init
 ****************************************/

bool round_object_init(RoundObject *obj)
{
  if (!obj)
    return false;
  
  obj->mutex = round_mutex_new();
  if (!obj->mutex)
    return false;
  
  obj->refCnt = 0;
  
  return true;
}

/****************************************
 * round_object_waitrelease
 ****************************************/

bool round_object_waitrelease(RoundObject *obj)
{
  if (!obj)
    return false;
  
  // TODO Support lazy refence counting

  if (!round_mutex_lock(obj->mutex))
    return false;
  
  if (obj->refCnt != 0) {
    if (!round_mutex_unlock(obj->mutex))
      return false;
    while (true) {
      round_wait(0.5);
      if (!round_mutex_lock(obj->mutex))
        return false;
      if (obj->refCnt == 0)
        break;
      if (!round_mutex_unlock(obj->mutex))
        return false;
    }
  }

  if (!round_mutex_unlock(obj->mutex))
    return false;

  return true;
}

/****************************************
 * round_object_delete
 ****************************************/

bool round_object_delete(RoundObject *obj)
{
  if (!obj)
    return false;
  
  if (!round_object_waitrelease(obj))
    return false;
  
  round_mutex_delete(obj->mutex);
  
  free(obj);
  
  return true;
}

/****************************************
 * round_object_alloc
 ****************************************/

bool round_object_alloc(RoundObject *obj)
{
  if (!obj)
    return false;
  
  round_mutex_lock(obj->mutex);
  obj->refCnt++;
  round_mutex_unlock(obj->mutex);

  return true;
}

/****************************************
 * round_object_release
 ****************************************/

bool round_object_release(RoundObject *obj)
{
  if (!obj)
    return false;
  
  round_mutex_lock(obj->mutex);
  obj->refCnt--;
  round_mutex_unlock(obj->mutex);
  
  return true;
}
