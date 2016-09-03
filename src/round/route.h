/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_ROUTE_H_
#define _ROUND_ROUTE_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <round/util/strings.h>
#include <round/util/map.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Constants
 ****************************************/

typedef enum {
  RoundRouteObjectNone = 0x00,
  RoundRouteTriggerObject = 0x01,
  RoundRouteMethodObject = 0x02,
} RoundRouteObjectType;

/****************************************
 * Data Type
 ****************************************/

typedef void RoundRouteTarget;
  
typedef struct {
  RoundString *name;
  RoundRouteObjectType type;
  RoundRouteTarget *target;
} RoundRouteObject;

typedef struct {
  RoundString *name;
  RoundRouteObject *srcObj;
  RoundRouteObject *destObj;
} RoundRoute;

typedef struct {
  RoundMap *map;
} RoundRouteManager;
  
/****************************************
 * Function (Route Object)
 ****************************************/
  
RoundRouteObject* round_route_object_new();
bool round_route_object_delete(RoundRouteObject* obj);

#define round_route_object_setname(obj, val) round_string_setvalue(obj->name, val)
#define round_route_object_getname(obj) round_string_getvalue(obj->name)
#define round_route_object_hasname(obj) round_string_hasvalue(obj->name)

#define round_route_object_settype(obj, value) (obj->type = value)
#define round_route_object_gettype(obj) (obj->type)
#define round_route_object_istrigger(obj) ((obj->type == RoundRouteTriggerObject) ? true : false)
#define round_route_object_ismethod(obj) ((obj->type == RoundRouteMethodObject) ? true : false)
  
#define round_route_object_settarget(obj, value) (obj->target = value)
#define round_route_object_gettarget(obj) (obj->target)
#define round_route_object_hastarget(obj) ((obj->target) ? true : false)
#define round_route_object_gettrigger(obj) ((RoundTrigger *)(obj->target))
#define round_route_object_getmethod(obj) ((RoundMethod *)(obj->target))

/****************************************
 * Function (Route)
 ****************************************/
  
RoundRoute *round_route_new();
bool round_route_delete(RoundRoute *route);
  
#define round_route_setname(route, val) round_string_setvalue(route->name, val)
#define round_route_getname(route) round_string_getvalue(route->name)
#define round_route_hasname(route) round_string_hasvalue(route->name)

#define round_route_getsourceobject(route) (route->srcObj)
#define round_route_hassourceobject(route) ((route->srcObj) ? true : false)
#define round_route_getdestinationobject(route) (route->destObj)
#define round_route_hasdestinationobject(route) ((route->destObj) ? true : false)

/****************************************
 * Function (Manager)
 ****************************************/
  
RoundRouteManager *round_route_manager_new();
bool round_route_manager_delete(RoundRouteManager *mgr);

bool round_route_manager_setroute(RoundRouteManager *mgr, RoundRoute *route);

#define round_route_manager_getbyname(mgr, name) round_map_getobjectbykey(mgr->map, name)
#define round_route_manager_removeroute(mgr, route) round_map_removeobjectbykey(mgr->map, round_route_getname(route))
#define round_route_manager_removeroutebyname(mgr, name) round_map_removeobjectbykey(mgr->map, name)
#define round_route_manager_size(mgr) round_map_size(mgr->map)
  
#ifdef  __cplusplus
}
#endif

#endif
