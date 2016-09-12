/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_ROUTE_INTERNAL_H_
#define _ROUND_ROUTE_INTERNAL_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <round/route.h>

#ifdef  __cplusplus
extern "C" {
#endif

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
