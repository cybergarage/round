/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_RUBY_ENGINE_H_
#define _ROUNDC_RUBY_ENGINE_H_

#include <round/script.h>

#if defined(ROUND_SUPPORT_MRUBY)
#include <mruby.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct _RoundRubyEngine {
  RoundMutex *mutex;
  char *result;
  char *error;
#if defined(ROUND_SUPPORT_MRUBY)
  mrb_state *mrb;
#endif
} RoundRubyEngine;

RoundRubyEngine *round_ruby_engine_new();
bool round_ruby_engine_delete(RoundRubyEngine *jsEngine);

bool round_ruby_engine_lock(RoundRubyEngine *jsEngine);
bool round_ruby_engine_unlock(RoundRubyEngine *jsEngine);
  
bool round_ruby_engine_setresult(RoundRubyEngine *jsEngine, const char *value);
const char *round_ruby_engine_getresult(RoundRubyEngine *jsEngine);

bool round_ruby_engine_seterror(RoundRubyEngine *jsEngine, const char *value);
const char *round_ruby_engine_geterror(RoundRubyEngine *jsEngine);

bool round_ruby_engine_run(RoundRubyEngine *luaErubyEnginengine, const char *source, const char *func, const char *param);
  
#ifdef  __cplusplus
}
#endif

#endif