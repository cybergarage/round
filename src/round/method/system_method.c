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
 * round_system_method_new
 ****************************************/

RoundMethod* round_system_method_new(const char* name,
                                     ROUND_SCRIPT_NATIVE_ENGINE_FUNC func,
                                     bool isFinal)
{
  RoundMethod* method;

  method = round_method_new();
  if (!method)
    return NULL;

  round_method_setlanguage(method, RoundNativeEngineLanguage);
  round_method_setname(method, name);
  round_method_setuserdata(method, func);
  round_method_setfinal(method, isFinal);
  round_method_setstatic(method, true);

  return method;
}
