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

RoundMethod* round_method_new()
{
  RoundMethod* method;

  method = (RoundMethod*)malloc(sizeof(RoundMethod));
  if (!method)
    return NULL;

  method->module = NULL;
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

bool round_method_delete(RoundMethod* method)
{
  if (!method)
    return false;

  round_method_setcode(method, NULL, 0);

  if (method->module) {
    free(method->module);
  }

  if (method->name) {
    free(method->name);
  }

  if (method->lang) {
    free(method->lang);
  }

  if (method->code) {
    free(method->code);
  }

  free(method);

  return true;
}

/****************************************
 * round_method_isvalid
 ****************************************/

bool round_method_isvalid(RoundMethod* method)
{
  if (!method)
    return false;

  if (round_strlen(method->name) <= 0)
    return false;

  if (round_method_isdynamic(method)) {
    if (!method->code)
      return false;
    if (method->codeSize <= 0)
      return false;
  }

  return true;
}

/****************************************
 * round_method_setmodule
 ****************************************/

bool round_method_setmodule(RoundMethod* method, const char* module)
{
  if (!method)
    return false;

  return round_strloc(module, &method->module);
}

/****************************************
 * round_method_setname
 ****************************************/

bool round_method_setname(RoundMethod* method, const char* name)
{
  if (!method)
    return false;

  return round_strloc(name, &method->name);
}

/****************************************
 * round_method_setlanguage
 ****************************************/

bool round_method_setlanguage(RoundMethod* method, const char* lang)
{
  if (!method)
    return false;

  return round_strloc(lang, &method->lang);
}

/****************************************
 * round_method_setcode
 ****************************************/

bool round_method_setcode(RoundMethod* method, byte* code, size_t codeSize)
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

  method->code = (byte*)malloc(codeSize + 1);
  if (!method->code)
    return false;

  memcpy(method->code, code, codeSize);
  method->code[codeSize] = '\0';

  method->codeSize = codeSize;

  return true;
}

/****************************************
 * round_method_setstringcode
 ****************************************/

bool round_method_setstringcode(RoundMethod* method, const char* code)
{
  return round_method_setcode(method, (byte*)code, round_strlen(code) + 1);
}
