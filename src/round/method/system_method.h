/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_SYSTEM_METHOD_H_
#define _ROUNDC_SYSTEM_METHOD_H_

#include <round/method.h>
#include <round/script/native.h>

#ifdef  __cplusplus
extern "C" {
#endif

RoundMethod *round_system_method_new(const char *name, ROUND_SCRIPT_NATIVE_ENGINE_FUNC func);
  
bool round_system_method_setmethod(RoundLocalNode *node, const char *param, RoundString *result, RoundError *err);
  
#ifdef  __cplusplus
}
#endif

#endif