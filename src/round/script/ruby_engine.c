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
#include <round/script/ruby.h>

#if defined(ROUND_SUPPORT_MRUBY)
#include "mruby/compile.h"
#endif

#/****************************************
* round_ruby_engine_new
****************************************/

RoundRubyEngine *round_ruby_engine_new()
{
  RoundRubyEngine *rubyEngine;
  
  rubyEngine = (RoundRubyEngine *)calloc(1, sizeof(RoundRubyEngine));
  if (!rubyEngine)
    return NULL;

  if (!round_script_engine_init((RoundScriptEngine *)rubyEngine)) {
    round_ruby_engine_delete(rubyEngine);
    return NULL;
  }
 
#if defined(ROUND_SUPPORT_MRUBY)
  rubyEngine->mrb = mrb_open() ;
#endif
  
  return rubyEngine;
}

/****************************************
 * round_ruby_engine_delete
 ****************************************/

bool round_ruby_engine_delete(RoundRubyEngine *rubyEngine) {
  if (!rubyEngine)
    return false;
  
#if defined(ROUND_SUPPORT_MRUBY)
  mrb_close(rubyEngine->mrb);
#endif
  
  return round_script_engine_delete((RoundScriptEngine *)rubyEngine);
}

/****************************************
 * round_ruby_engine_setresult
 ****************************************/

bool round_ruby_engine_setresult(RoundRubyEngine *rubyEngine, const char *value) {
  return round_script_engine_setresult((RoundScriptEngine *)rubyEngine, value);
}

/****************************************
 * round_ruby_engine_getresult
 ****************************************/

const char *round_ruby_engine_getresult(RoundRubyEngine *rubyEngine) {
  return round_script_engine_getresult((RoundScriptEngine *)rubyEngine);
}

/****************************************
 * round_ruby_engine_seterror
 ****************************************/

bool round_ruby_engine_seterror(RoundRubyEngine *rubyEngine, const char *value) {
  return round_script_engine_seterror((RoundScriptEngine *)rubyEngine, value);
}

/****************************************
 * round_ruby_engine_geterror
 ****************************************/

const char *round_ruby_engine_geterror(RoundRubyEngine *rubyEngine) {
  return round_script_engine_geterror((RoundScriptEngine *)rubyEngine);
}

/****************************************
 * round_ruby_engine_lock
 ****************************************/

bool round_ruby_engine_lock(RoundRubyEngine *rubyEngine) {
  return round_script_engine_lock((RoundScriptEngine *)rubyEngine);
}

/****************************************
 * round_ruby_engine_unlock
 ****************************************/

bool round_ruby_engine_unlock(RoundRubyEngine *rubyEngine) {
  return round_script_engine_unlock((RoundScriptEngine *)rubyEngine);
}

/****************************************
 * round_ruby_engine_run
 ****************************************/

bool round_ruby_engine_run(RoundRubyEngine *rubyEngine, const char *source, const char *func, const char *param) {
  return false;
}

bool round_ruby_engine_run_code(RoundRubyEngine *rubyEngine, const char *code) {
#if defined(ROUND_SUPPORT_MRUBY)
#endif
  
  if (!rubyEngine)
    return false;
  
#if defined(ROUND_SUPPORT_MRUBY)
  mrb_load_string(rubyEngine->mrb, code);
  return true;
#else
  return false;
#endif
}
