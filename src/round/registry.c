/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/registry.h>

/****************************************
 * round_registry_init
 ****************************************/

bool round_registry_init(RoundRegistry *reg)
{
  reg->key = round_string_new();
  reg->value = round_string_new();
  
  if (!reg->key || !reg->value)
    return false;
  
  return true;
}

/****************************************
 * round_registry_new
 ****************************************/

RoundRegistry *round_registry_new()
{
  RoundRegistry *reg;
  
  reg = (RoundRegistry *)malloc(sizeof(RoundRegistry));
  if (!reg)
    return NULL;

  if (!round_registry_init(reg)) {
    round_registry_delete(reg);
    return NULL;
  }

  return reg;
}

/****************************************
 * round_registry_delete
 ****************************************/

bool round_registry_delete(RoundRegistry *reg)
{
  if (!reg)
    return false;
  
  round_string_delete(reg->key);
  round_string_delete(reg->value);

  free(reg);
  
  return true;
}
