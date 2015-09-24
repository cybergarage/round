/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_REGISTRY_H_
#define _ROUNDC_REGISTRY_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <round/util/strings.h>
#include <round/util/map.h>

#ifdef  __cplusplus
extern "C" {
#endif
  
/****************************************
 * Data Type
 ****************************************/
  
typedef struct {
  RoundString *key;
  RoundString *value;
} RoundRegistry;

typedef struct {
  RoundMap *map;
} RoundRegistryManager;

/****************************************
 * Function
 ****************************************/
  
RoundRegistry *round_registry_new();
bool round_registry_delete(RoundRegistry *registry);
  
#define round_registry_setkey(reg, val) round_string_setvalue(reg->key, val)
#define round_registry_getkey(reg) round_string_getvalue(reg->key)

#define round_registry_setvalue(reg, val) round_string_setvalue(reg->value, val)
#define round_registry_getvalue(reg) round_string_getvalue(reg->value)

/****************************************
 * Function (Map)
 ****************************************/
  
RoundMap *round_registry_map_new();
  
#define round_registry_map_delete(map) round_map_delete(map)
#define round_registry_map_size(map) round_map_size(map)
#define round_registry_map_set(map, reg) round_map_setobject(map, round_registry_getkey(reg), reg)
#define round_registry_map_get(map, name) ((RoundRegistry*)round_map_getobjectbykey(map, name))
#define round_registry_map_remove(map, name) round_map_removeobjectbykey(map, name)

/****************************************
 * Function (Manager)
 ****************************************/
  
RoundRegistryManager *round_registry_manager_new();
bool round_registry_manager_delete(RoundRegistryManager *mgr);
  
#define round_registry_manager_set(mgr, reg) round_registry_map_set(mgr->map, reg)
#define round_registry_manager_get(mgr, name) round_registry_map_get(mgr->map, name)
#define round_registry_manager_remove(mgr, name) round_registry_map_remove(mgr->map, name)
#define round_registry_manager_size(mgr) round_registry_map_size(mgr->map)
  
#ifdef  __cplusplus
}
#endif

#endif
