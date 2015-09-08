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

#include <round/script_internal.h>

#if defined(ROUND_SUPPORT_RUBY)
#if defined(__APPLE__)
#include <Ruby/ruby.h>
#else
#include <ruby.h>
#endif
#elif defined(ROUND_SUPPORT_MRUBY)
#include <mruby.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct _RoundRubyEngine {
  RoundMutex *mutex;
  char *lang;
  ROUND_SCRIPT_ENGINE_EXECFUNC execFunc;
  ROUND_SCRIPT_ENGINE_DESTRUCTOR destFunc;
#if defined(ROUND_SUPPORT_MRUBY)
  mrb_state *mrb;
#endif
} RoundRubyEngine;

RoundRubyEngine *round_ruby_engine_new();
bool round_ruby_engine_delete(RoundRubyEngine *engine);

bool round_ruby_engine_lock(RoundRubyEngine *engine);
bool round_ruby_engine_unlock(RoundRubyEngine *engine);
  
bool round_ruby_engine_setresult(RoundRubyEngine *engine, const char *value);
const char *round_ruby_engine_getresult(RoundRubyEngine *engine);

bool round_ruby_engine_seterror(RoundRubyEngine *engine, const char *value);
const char *round_ruby_engine_geterror(RoundRubyEngine *engine);

bool round_ruby_engine_run(RoundRubyEngine *engine, RoundScript *script, const char *param, RoundString *result, RoundError *err);
  
#ifdef  __cplusplus
}
#endif

#endif