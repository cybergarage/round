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

#include <round/const.h>
#include <round/method.h>
#include <round/script/native.h>

#ifdef  __cplusplus
extern "C" {
#endif

RoundMethod *round_system_method_new(const char *name, ROUND_SCRIPT_NATIVE_ENGINE_FUNC func, bool isFinal);
  
bool round_system_method_setmethod(RoundLocalNode *node, const char *param, RoundString *result, RoundError *err);
bool round_system_method_removemethod(RoundLocalNode *node, const char *param, RoundString *result, RoundError *err);

bool round_system_method_setregistry(RoundLocalNode *node, const char *param, RoundString *result, RoundError *err);
bool round_system_method_getregistry(RoundLocalNode *node, const char *param, RoundString *result, RoundError *err);
bool round_system_method_removeregistry(RoundLocalNode *node, const char *param, RoundString *result, RoundError *err);

#define round_system_method_setmethod_new() round_system_method_new(ROUNDC_SYSTEM_METHOD_SET_METHOD, round_system_method_setmethod, true)
#define round_system_method_removemethod_new() round_system_method_new(ROUNDC_SYSTEM_METHOD_REMOVE_METHOD, round_system_method_removemethod, true)

#define round_system_method_setregistry_new() round_system_method_new(ROUNDC_SYSTEM_METHOD_SET_REGISTRY, round_system_method_setregistry, false)
#define round_system_method_getregistry_new() round_system_method_new(ROUNDC_SYSTEM_METHOD_GET_REGISTRY, round_system_method_getregistry, false)
#define round_system_method_removeregistry_new() round_system_method_new(ROUNDC_SYSTEM_METHOD_REMOVE_REGISTRY, round_system_method_removeregistry, false)

#ifdef  __cplusplus
}
#endif

#endif