/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_FINDER_INTERNAL_H_
#define _ROUND_FINDER_INTERNAL_H_

#include <round/typedef.h>
#include <round/const.h>

#include <mupnp/controlpoint.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/
  
typedef void (*ROUND_FINDER_NODEADDED_LISTNER)(void *, void *);
typedef void (*ROUND_FINDER_NODEREMOVED_LISTNER)(void *, void *);

typedef struct {
  mUpnpControlPoint *cp;
  void *userData;
  ROUND_FINDER_NODEADDED_LISTNER addedListener;
  ROUND_FINDER_NODEREMOVED_LISTNER removedListener;
} RoundFinder;

/****************************************
 * Public Header
 ****************************************/
  
#include <round/finder.h>

#define round_finder_setuserdata(finder,value) (finder->userData = value)
#define round_finder_getuserdata(finder) (finder->userData)

#define round_finder_setnodeaddedlistener(finder,func) (finder->addedListener = (ROUND_FINDER_NODEADDED_LISTNER)func)
#define round_finder_getnodeaddedlistener(finder) (finder->addedListener)

#define round_finder_setnoderemovedlistener(finder,func) (finder->removedListener = (ROUND_FINDER_NODEREMOVED_LISTNER)func)
#define round_finder_getnoderemovedlistener(finder) (finder->removedListener)
  
/****************************************
 * Function
 ****************************************/
  
#ifdef  __cplusplus
} /* extern C */
#endif

#endif /* _ROUND_FINDER_INTERNAL_H_ */
