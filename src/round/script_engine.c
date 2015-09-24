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
#include <round/script.h>

/****************************************
 * round_script_engine_new
 ****************************************/

RoundScriptEngine *round_script_engine_new()
{
  RoundScriptEngine *engine;
  
  engine = (RoundScriptEngine *)malloc(sizeof(RoundScriptEngine));
  if (!engine)
    return NULL;
  
  if (!round_script_engine_init(engine)) {
    round_script_engine_delete(engine);
    return NULL;
  }
  
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
  round_script_engine_setoption(engine, 0);
  round_script_engine_setexecutefunc(engine, NULL);
  round_oo_setdescendantdestoroyfunc(engine, NULL);
  round_script_engine_setlocalnode(engine, NULL);

  return true;
}

/****************************************
 * round_script_engine_destory
 ****************************************/

bool round_script_engine_destory(RoundScriptEngine *engine)
{
  if (!engine)
    return false;
  
  if (engine->mutex) {
    round_mutex_delete(engine->mutex);
    engine->mutex = NULL;
  }
  
  if (engine->lang) {
    free(engine->lang);
    engine->lang = NULL;
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
  
  if (!round_oo_execdescendantdestoroy(engine))
    return false;

  if (!round_script_engine_destory(engine))
    return false;
  
  return true;
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

/****************************************
 * round_script_engine_isvalid
 ****************************************/

bool round_script_engine_isvalid(RoundScriptEngine *engine)
{
  if (!engine)
    return false;
  
  if (round_strlen(engine->lang) <= 0)
    return false;
  
  return true;
}
