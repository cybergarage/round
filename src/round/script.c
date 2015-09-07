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
  
  script->name = NULL;
  script->lang = NULL;
  script->code = NULL;
  script->codeSize = 0;
  
  return script;
}

/****************************************
 * round_script_delete
 ****************************************/

bool round_script_delete(RoundScript *script)
{
  if (!script)
    return false;
  
  round_script_setcode(script, NULL, 0);
  
  free(script);
  
  return true;
}

/****************************************
 * round_script_isvalid
 ****************************************/

bool round_script_isvalid(RoundScript *script)
{
  if (!script)
    return false;

  if (round_strlen(script->name) <= 0)
    return false;
  
  if (!script->code)
    return false;
  
  if (script->codeSize <= 0)
    return false;

    return true;
}

/****************************************
 * round_script_setcode
 ****************************************/

bool round_script_setcode(RoundScript *script, byte *code, size_t codeSize)
{
  if (!script)
    return false;

  if (script->code) {
    free(script->code);
    script->code = NULL;
    script->codeSize = 0;
  }

  if (!code || (codeSize == 0))
    return true;
  
  script->code = (byte *)malloc(codeSize);
  if (!script->code)
    return false;
  
  
  memcpy(script->code, code, codeSize);
  script->codeSize = codeSize;
  
  return true;
}
