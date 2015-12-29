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
#include <round/script/python.h>

/****************************************
* round_python_engine_new
****************************************/

RoundPythonEngine* round_python_engine_new()
{
  RoundPythonEngine* engine;

  engine = (RoundPythonEngine*)calloc(1, sizeof(RoundPythonEngine));
  if (!engine)
    return NULL;

  if (!round_python_engine_init(engine)) {
    round_python_engine_delete(engine);
    return NULL;
  }

  return engine;
}

/****************************************
 * round_python_engine_init
 ****************************************/

bool round_python_engine_init(RoundPythonEngine* engine)
{
  if (!engine)
    return false;
  
  if (!round_script_engine_init((RoundScriptEngine*)engine))
    return false;
  
  round_script_engine_setlanguage(engine, RoundPythonEngineLanguage);
  round_script_engine_setexecutefunc(engine, round_python_engine_run);
  round_oo_setdescendantdestoroyfunc(engine, round_python_engine_destory);
  
  return true;
}

/****************************************
 * round_python_engine_destory
 ****************************************/

bool round_python_engine_destory(RoundPythonEngine* engine)
{
  if (!engine)
    return false;

  return true;
}

/****************************************
 * round_python_engine_delete
 ****************************************/

bool round_python_engine_delete(RoundPythonEngine* engine)
{
  if (!engine)
    return false;

  if (!round_python_engine_destory(engine))
    return false;

  if (!round_script_engine_destory((RoundScriptEngine*)engine))
    return false;

  free(engine);

  return true;
}


/****************************************
 * round_python_engine_run
 ****************************************/

bool round_python_engine_run(RoundPythonEngine* engine, RoundMethod* method, const char* param, RoundString* result, RoundError* err)
{
  const char* source;
  const char* name;

  if (!engine)
    return false;

  name = round_method_getname(method);
  source = round_method_getstringcode(method);

  return true;
}
