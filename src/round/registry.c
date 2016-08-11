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

bool round_registry_init(RoundRegistry* reg)
{
  reg->key = round_string_new();

  if (!reg->key)
    return false;

  round_registry_settype(reg, RoundRegistryTypeUnknown);
  round_registry_setts(reg, 0);
  round_registry_setlts(reg, 0);

  return true;
}

/****************************************
 * round_registry_new
 ****************************************/

RoundRegistry* round_registry_new()
{
  RoundRegistry* reg;

  reg = (RoundRegistry*)malloc(sizeof(RoundRegistry));
  if (!reg)
    return NULL;

  if (!round_registry_init(reg)) {
    round_registry_delete(reg);
    return NULL;
  }

  return reg;
}

/****************************************
 * round_registry_clear
 ****************************************/

bool round_registry_clear(RoundRegistry *reg)
{
  if (!reg)
    return false;
  
  round_string_clear(reg->key);
  if (round_registry_isstring(reg)) {
    if (!reg->value.string) {
      round_string_delete(reg->value.string);
      reg->value.string = NULL;
    }
  }
  
  round_registry_settype(reg, RoundRegistryTypeUnknown);
  
  return true;
}

/****************************************
>>>>>>> 566d35b2ed7da3627d6874c198c69fba95f8de12
 * round_registry_delete
 ****************************************/

bool round_registry_delete(RoundRegistry* reg)
{
  if (!reg)
    return false;

  round_registry_clear(reg);
  round_string_delete(reg->key);

  free(reg);

  return true;
}

/****************************************
 * round_registry_setstring
 ****************************************/

bool round_registry_setstring(RoundRegistry *reg, const char *val)
{
  if (!reg)
    return false;
  
  if (!round_registry_isstring(reg)) {
    if (!round_registry_isunknown(reg))
      return false;
    reg->value.string = round_string_new();
    round_registry_settype(reg, RoundRegistryTypeString);
  }
  
  round_string_setvalue(reg->value.string, val);
  
  return true;
}

/****************************************
 * round_registry_getstring
 ****************************************/

bool round_registry_getstring(RoundRegistry *reg, const char **val)
{
  if (!reg)
    return false;
  
  if (!round_registry_isstring(reg))
    return false;
  
  *val = round_string_getvalue(reg->value.string);
  
  return true;
}

/****************************************
 * round_registry_setinteger
 ****************************************/

bool round_registry_setinteger(RoundRegistry *reg, int val)
{
  if (!reg)
    return false;
  
  if (!round_registry_isinteger(reg)) {
    if (!round_registry_isunknown(reg))
      return false;
    round_registry_settype(reg, RoundRegistryTypeInteger);
    reg->value.integer = 0;
  }

  reg->value.integer = val;
  
  return true;
}

/****************************************
 * round_registry_getinteger
 ****************************************/

bool round_registry_getinteger(RoundRegistry *reg, int *val)
{
  if (!reg)
    return false;
  
  if (!round_registry_isinteger(reg))
    return false;
  
  *val = reg->value.integer;
  
  return true;
}

/****************************************
 * round_registry_setreal
 ****************************************/

bool round_registry_setreal(RoundRegistry *reg, double val)
{
  if (!reg)
    return false;
  
  if (!round_registry_isreal(reg)) {
    if (!round_registry_isunknown(reg))
      return false;
    round_registry_settype(reg, RoundRegistryTypeReal);
    reg->value.real = 0.0;
  }
  
  reg->value.real = val;
  
  return true;
}

/****************************************
 * round_registry_getreal
 ****************************************/

bool round_registry_getreal(RoundRegistry *reg, double *val)
{
  if (!reg)
    return false;
  
  if (!round_registry_isreal(reg))
    return false;
  
  *val = reg->value.real;
  
  return true;
}
