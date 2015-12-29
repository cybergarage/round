/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_NATIVE_ENGINE_H_
#define _ROUND_NATIVE_ENGINE_H_

#include <round/script.h>
#include <round/method.h>
#include <round/node_internal.h>
#include <round/util/json_internal.h>

#ifdef  __cplusplus
extern "C" {
#endif
  
#define RoundNativeEngineLanguage "c"
  
typedef struct {
  ROUND_SCRIPT_ENGINE_STRUCT_MEMBERS
} RoundNativeEngine;

RoundNativeEngine *round_native_engine_new();
bool round_native_engine_init(RoundNativeEngine* engine);
bool round_native_engine_destory(RoundNativeEngine *engine);
bool round_native_engine_delete(RoundNativeEngine *engine);
  
bool round_native_engine_run(RoundNativeEngine *engine, RoundMethod *method, const char *params, RoundJSONObject **result, RoundError *err);

#ifdef  __cplusplus
}
#endif

#endif