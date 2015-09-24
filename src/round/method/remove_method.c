/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/method/system_method.h>

/****************************************
 * round_system_method_removemethod
 ****************************************/

bool round_system_method_removemethod(RoundLocalNode *node, const char *param, RoundString *result, RoundError *err)
{
  RoundJSON *json;
  const char *name;
  bool isRemoved;
  
  json = round_json_new();
  
  if (round_json_parse(json, param, err)) {
    round_json_delete(json);
    return false;
  }
  
  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_NAME, &name)) {
    round_json_delete(json);
    return false;
  }

  if (round_local_node_isfinalmethod(node, name)) {
    round_json_delete(json);
    return false;
  }

  isRemoved = round_local_node_removemethod(node, name);

  round_json_delete(json);

  return isRemoved;
}
