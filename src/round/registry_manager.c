/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdlib.h>
#include <round/const.h>
#include <round/error_internal.h>
#include <round/registry.h>

/****************************************
 * round_registry_manager_new
 ****************************************/

RoundRegistryManager *round_registry_manager_new() {
  RoundRegistryManager *mgr;

  mgr = (RoundRegistryManager *)malloc(sizeof(RoundRegistryManager));
  if (!mgr)
    return NULL;

  mgr->map = round_registry_map_new();

  return mgr;
}

/****************************************
 * round_registry_manager_delete
 ****************************************/

bool round_registry_manager_delete(RoundRegistryManager *mgr) {
  if (!mgr)
    return false;

  round_registry_map_delete(mgr->map);

  free(mgr);

  return true;
}
