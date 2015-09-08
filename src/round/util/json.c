/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/json.h>

/****************************************
* round_json_new
****************************************/

RoundJSON *round_json_new(void)
{
  RoundJSON *json;
  
  json = (RoundJSON *)malloc(sizeof(RoundJSON));
  
  if (!json)
    return NULL;
  
  return json;
}

/****************************************
 * round_json_delete
 ****************************************/

bool round_json_delete(RoundJSON *json)
{
  if (!json)
    return false;
  
  free(json);
  
  return true;
}
