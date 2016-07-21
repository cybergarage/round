/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_REGISTRY_H_
#define _ROUND_REGISTRY_H_

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

typedef enum {
  RoundRegistryTypeUnknown = 0x0000,
  RoundRegistryTypeString = 0x0001,
  RoundRegistryTypeInteger = 0x0002,
  RoundRegistryTypeReal = 0x0004,
  RoundRegistryTypeJSON = 0x0005, // Not Implemented
} RoundRegistryType;

typedef union _RoundRegistryValue {
  RoundString *string;
  int integer;
  double real;
} RoundRegistryValue;

typedef struct {
  RoundString *key;
  RoundRegistryType type;
  RoundRegistryValue value;
  clock_t ts;
  clock_t lts;
} RoundRegistry;

typedef struct {
  RoundMap *map;
} RoundRegistryManager;

/****************************************
 * Function
 ****************************************/
  
RoundRegistry *round_registry_new();
bool round_registry_clear(RoundRegistry *reg);
bool round_registry_delete(RoundRegistry *reg);

#define round_registry_settype(reg, val) (reg->type = val)
#define round_registry_gettype(reg) (reg->type)
#define round_registry_istype(reg, val) (reg->type == val)
#define round_registry_isunknown(reg) (reg->type == RoundRegistryTypeUnknown)
#define round_registry_isstring(reg) (reg->type == RoundRegistryTypeString)
#define round_registry_isinteger(reg) (reg->type == RoundRegistryTypeInteger)
#define round_registry_isreal(reg) (reg->type == RoundRegistryTypeReal)

#define round_registry_setkey(reg, val) round_string_setvalue(reg->key, val)
#define round_registry_getkey(reg) round_string_getvalue(reg->key)

bool round_registry_setstring(RoundRegistry *reg, const char *val);
bool round_registry_getstring(RoundRegistry *reg, const char **val);

bool round_registry_setinteger(RoundRegistry *reg, int val);
bool round_registry_getinteger(RoundRegistry *reg, int *val);

bool round_registry_setreal(RoundRegistry *reg, double val);
bool round_registry_getreal(RoundRegistry *reg, double *val);

#define round_registry_setts(reg, val) (reg->ts = val)
#define round_registry_getts(reg) (reg->ts)

#define round_registry_setlts(reg, val) (reg->lts = val)
#define round_registry_getlts(reg) (reg->lts)

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
