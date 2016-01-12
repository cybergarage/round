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

/****************************************
* round_ruby_engine_new
****************************************/

RoundRubyEngine* round_ruby_engine_new()
{
  RoundRubyEngine* engine;

  engine = (RoundRubyEngine*)calloc(1, sizeof(RoundRubyEngine));
  if (!engine)
    return NULL;

  if (!round_ruby_engine_init(engine)) {
    round_ruby_engine_delete(engine);
    return NULL;
  }

  return engine;
}

/****************************************
 * round_ruby_engine_init
 ****************************************/

bool round_ruby_engine_init(RoundRubyEngine* engine)
{
  if (!engine)
    return false;

  if (!round_script_engine_init((RoundScriptEngine*)engine))
    return false;

  round_script_engine_setlanguage(engine, RoundRubyEngineLanguage);
  round_script_engine_setexecutefunc(engine, round_ruby_engine_run);
  round_oo_setdescendantdestoroyfunc(engine, round_ruby_engine_destory);

#if defined(ROUND_SUPPORT_RUBY)
  ruby_init();
  ruby_init_loadpath();
#elif defined(ROUND_SUPPORT_MRUBY)
  engine->mrb = mrb_open();
#endif

  return true;
}

/****************************************
 * round_ruby_engine_destory
 ****************************************/

bool round_ruby_engine_destory(RoundRubyEngine* engine)
{
  if (!engine)
    return false;

#if defined(ROUND_SUPPORT_RUBY)
  ruby_cleanup(0);
#elif defined(ROUND_SUPPORT_MRUBY)
  mrb_close(engine->mrb);
#endif

  return true;
}

/****************************************
 * round_ruby_engine_delete
 ****************************************/

bool round_ruby_engine_delete(RoundRubyEngine* engine)
{
  if (!engine)
    return false;

  if (!round_ruby_engine_destory(engine))
    return false;

  if (!round_script_engine_destory((RoundScriptEngine*)engine))
    return false;

  free(engine);

  return true;
}

/****************************************
 * round_ruby_engine_getsoucecode
 ****************************************/

bool round_ruby_engine_getsoucecode(RoundRubyEngine* engine, RoundMethod* method, const char* param, RoundString* sourceCode)
{
  if (!method || !sourceCode)
    return false;

  return true;
}

/****************************************
 * round_ruby_engine_run
 ****************************************/

bool round_ruby_engine_run(RoundRubyEngine* engine, RoundMethod* method, const char* param, RoundJSONObject** jsonResult, RoundError* err)
{
  RoundString *sourceCode, *strResult;
  bool isSuccess;

  if (!engine)
    return false;

  sourceCode = round_string_new();
  strResult = round_string_new();

  if (round_ruby_engine_getsoucecode(engine, method, param, sourceCode)) {
    isSuccess = round_ruby_engine_run_code(engine, round_string_getvalue(sourceCode));
  }

  *jsonResult = NULL;
  if (isSuccess) {
    isSuccess = round_script_result2json(strResult, jsonResult, err);
  }

  if (sourceCode) {
    round_string_delete(sourceCode);
  }

  if (strResult) {
    round_string_delete(strResult);
  }

  return isSuccess;
}

/****************************************
 * round_ruby_engine_run
 ****************************************/

bool round_ruby_engine_run_code(RoundRubyEngine* engine, const char* code)
{
  if (!engine)
    return false;

#if defined(ROUND_SUPPORT_RUBY)
  int evalState;
  rb_eval_string_protect(code, &evalState);
  if (evalState) {
    // round_ruby_engine_seterror(engine, rb_string_value_cstr((volatile VALUE *)rb_errinfo));
  }

  return true;
#elif defined(ROUND_SUPPORT_MRUBY)
  mrb_load_string(engine->mrb, code);
  return true;
#endif

  return false;
}
