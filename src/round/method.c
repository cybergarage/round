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
#include <round/method.h>

/****************************************
 * round_method_new
 ****************************************/

RoundMethod *round_method_new()
{
  RoundMethod *method;
  
  method = (RoundMethod *)malloc(sizeof(RoundMethod));
  if (!method)
    return NULL;
  
  method->name = NULL;
  method->lang = NULL;
  method->code = NULL;
  method->codeSize = 0;
  method->opt = 0;
  method->userData = NULL;
  
  return method;
}

/****************************************
 * round_method_delete
 ****************************************/

bool round_method_delete(RoundMethod *method)
{
  if (!method)
    return false;
  
  round_method_setcode(method, NULL, 0);
  
  free(method);
  
  return true;
}

/****************************************
 * round_method_isvalid
 ****************************************/

bool round_method_isvalid(RoundMethod *method)
{
  if (!method)
    return false;

  if (round_strlen(method->name) <= 0)
    return false;
  
  if (!method->code)
    return false;
  
  if (method->codeSize <= 0)
    return false;

    return true;
}

/****************************************
 * round_method_setcode
 ****************************************/

bool round_method_setcode(RoundMethod *method, byte *code, size_t codeSize)
{
  if (!method)
    return false;

  if (method->code) {
    free(method->code);
    method->code = NULL;
    method->codeSize = 0;
  }

  if (!code || (codeSize == 0))
    return true;
  
  method->code = (byte *)malloc(codeSize+1);
  if (!method->code)
    return false;
  
  memcpy(method->code, code, codeSize);
  method->code[codeSize] = '\0';
  
  method->codeSize = codeSize;
  
  return true;
}
