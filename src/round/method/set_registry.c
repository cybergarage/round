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
 * round_system_method_setmethod
 ****************************************/

bool round_system_method_setregistry(RoundLocalNode *node, const char *param, RoundString *result, RoundError *err)
{
  RoundJSON *json;
  const char *key, *val;
  bool isUpdated;
  
  json = round_json_new();
  
  if (round_json_parse(json, param, err)) {
    round_json_delete(json);
    return false;
  }
  
  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_KEY, &key)) {
    round_json_delete(json);
    return false;
  }
  
  if (!round_json_getstringforpath(json, ROUNDC_SYSTEM_METHOD_PARAM_VALUE, &val)) {
    round_json_delete(json);
    return false;
  }

  isUpdated = round_local_node_setregistry(node, key, val);
  
  round_json_delete(json);
  
  return isUpdated;
}
