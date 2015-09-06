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
#include <round/script_internal.h>

/****************************************
 * round_script_new
 ****************************************/

RoundScript *round_script_new()
{
  RoundScript *script;
  
  script = (RoundScript *)malloc(sizeof(RoundScript));
  if (!script)
    return NULL;
  
  return script;
}

/****************************************
 * round_script_delete
 ****************************************/

bool round_script_delete(RoundScript *script)
{
  if (!script)
    return false;
  
  free(script);
  
  return true;
}
