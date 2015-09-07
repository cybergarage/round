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
#include <round/script_internal.h>

/****************************************
 * round_script_engine_new
 ****************************************/

RoundScriptEngine *round_script_engine_new()
{
  RoundScriptEngine *engine;
  
  engine = (RoundScriptEngine *)malloc(sizeof(RoundScriptEngine));
  if (!engine)
    return NULL;
  
  round_script_engine_init(engine);
  
  return engine;
}

/****************************************
* round_script_engine_init
****************************************/

bool round_script_engine_init(RoundScriptEngine *engine)
{
  if (!engine)
    return false;

  round_list_node_init((RoundList *)engine);
  
  engine->mutex = round_mutex_new();
  if (!engine->mutex) {
    round_script_engine_delete(engine);
    return false;
  }
  
  engine->lang = NULL;
  engine->result = NULL;
  engine->error = NULL;
  
  return true;
}

/****************************************
 * round_script_engine_clear
 ****************************************/

bool round_script_engine_clear(RoundScriptEngine *engine)
{
  if (!engine)
    return false;
  
  if (engine->result) {
    free(engine->result);
    engine->result = NULL;
  }

  if (engine->error) {
    free(engine->error);
    engine->error = NULL;
  }

  return true;
}

/****************************************
 * round_script_engine_delete
 ****************************************/

bool round_script_engine_delete(RoundScriptEngine *engine)
{
  if (!engine)
    return false;
  
  if (!round_script_engine_clear(engine))
    return false;
  
  if (engine->mutex) {
    round_mutex_delete(engine->mutex);
    engine->mutex = NULL;
  }

  return true;
}

/****************************************
 * round_script_engine_setresult
 ****************************************/

bool round_script_engine_setresult(RoundScriptEngine *engine, const char *value)
{
  if (!engine)
    return false;
  return round_strloc(value, &engine->result);
}

/****************************************
 * round_script_engine_getresult
 ****************************************/

const char *round_script_engine_getresult(RoundScriptEngine *engine)
{
  if (!engine)
    return NULL;
  return engine->result;
}

/****************************************
 * round_script_engine_seterror
 ****************************************/

bool round_script_engine_seterror(RoundScriptEngine *engine, const char *value)
{
  if (!engine)
    return false;
  return round_strloc(value, &engine->error);
}

/****************************************
 * round_script_engine_geterror
 ****************************************/

const char *round_script_engine_geterror(RoundScriptEngine *engine)
{
  if (!engine)
    return NULL;
  return engine->error;
}

/****************************************
 * round_script_engine_lock
 ****************************************/

bool round_script_engine_lock(RoundScriptEngine *engine)
{
  if (!engine)
    return false;
  return round_mutex_lock(engine->mutex);
}

/****************************************
 * round_script_engine_unlock
 ****************************************/

bool round_script_engine_unlock(RoundScriptEngine *engine)
{
  if (!engine)
    return false;
  return round_mutex_unlock(engine->mutex);
}
