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
* round_script_engine_init
****************************************/

bool round_script_engine_init(RoundScriptEngine *scriptEngine) {
  if (!scriptEngine)
    return false;

  scriptEngine->result = NULL;
  scriptEngine->error = NULL;
  
  scriptEngine->mutex = round_mutex_new();
  if (!scriptEngine->mutex) {
    round_script_engine_delete(scriptEngine);
    return false;
  }

  return true;
}

/****************************************
 * round_script_engine_clear
 ****************************************/

bool round_script_engine_clear(RoundScriptEngine *scriptEngine) {
  if (!scriptEngine)
    return false;
  
  if (scriptEngine->result) {
    free(scriptEngine->result);
    scriptEngine->result = NULL;
  }

  if (scriptEngine->error) {
    free(scriptEngine->error);
    scriptEngine->error = NULL;
  }

  return true;
}

/****************************************
 * round_script_engine_delete
 ****************************************/

bool round_script_engine_delete(RoundScriptEngine *scriptEngine) {
  if (!scriptEngine)
    return false;
  
  if (!round_script_engine_clear(scriptEngine))
    return false;
  
  if (scriptEngine->mutex) {
    round_mutex_delete(scriptEngine->mutex);
    scriptEngine->mutex = NULL;
  }

  return true;
}

/****************************************
 * round_script_engine_setresult
 ****************************************/

bool round_script_engine_setresult(RoundScriptEngine *scriptEngine, const char *value) {
  if (!scriptEngine)
    return false;
  return round_strloc(value, &scriptEngine->result);
}

/****************************************
 * round_script_engine_getresult
 ****************************************/

const char *round_script_engine_getresult(RoundScriptEngine *scriptEngine) {
  if (!scriptEngine)
    return NULL;
  return scriptEngine->result;
}

/****************************************
 * round_script_engine_seterror
 ****************************************/

bool round_script_engine_seterror(RoundScriptEngine *scriptEngine, const char *value) {
  if (!scriptEngine)
    return false;
  return round_strloc(value, &scriptEngine->error);
}

/****************************************
 * round_script_engine_geterror
 ****************************************/

const char *round_script_engine_geterror(RoundScriptEngine *scriptEngine) {
  if (!scriptEngine)
    return NULL;
  return scriptEngine->error;
}

/****************************************
 * round_script_engine_lock
 ****************************************/

bool round_script_engine_lock(RoundScriptEngine *scriptEngine) {
  if (!scriptEngine)
    return false;
  return round_mutex_lock(scriptEngine->mutex);
}

/****************************************
 * round_script_engine_unlock
 ****************************************/

bool round_script_engine_unlock(RoundScriptEngine *scriptEngine) {
  if (!scriptEngine)
    return false;
  return round_mutex_unlock(scriptEngine->mutex);
}
