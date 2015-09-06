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
* round_script_engine_init
****************************************/

bool round_script_engine_init(RoundScriptEngine *eng) {
  if (!eng)
    return false;

  eng->result = NULL;
  eng->error = NULL;
  
  eng->mutex = round_mutex_new();
  if (!eng->mutex) {
    round_script_engine_delete(eng);
    return false;
  }

  return true;
}

/****************************************
 * round_script_engine_clear
 ****************************************/

bool round_script_engine_clear(RoundScriptEngine *eng) {
  if (!eng)
    return false;
  
  if (eng->result) {
    free(eng->result);
    eng->result = NULL;
  }

  if (eng->error) {
    free(eng->error);
    eng->error = NULL;
  }

  return true;
}

/****************************************
 * round_script_engine_delete
 ****************************************/

bool round_script_engine_delete(RoundScriptEngine *eng) {
  if (!eng)
    return false;
  
  if (!round_script_engine_clear(eng))
    return false;
  
  if (eng->mutex) {
    round_mutex_delete(eng->mutex);
    eng->mutex = NULL;
  }

  return true;
}

/****************************************
 * round_script_engine_setresult
 ****************************************/

bool round_script_engine_setresult(RoundScriptEngine *eng, const char *value) {
  if (!eng)
    return false;
  return round_strloc(value, &eng->result);
}

/****************************************
 * round_script_engine_getresult
 ****************************************/

const char *round_script_engine_getresult(RoundScriptEngine *eng) {
  if (!eng)
    return NULL;
  return eng->result;
}

/****************************************
 * round_script_engine_seterror
 ****************************************/

bool round_script_engine_seterror(RoundScriptEngine *eng, const char *value) {
  if (!eng)
    return false;
  return round_strloc(value, &eng->error);
}

/****************************************
 * round_script_engine_geterror
 ****************************************/

const char *round_script_engine_geterror(RoundScriptEngine *eng) {
  if (!eng)
    return NULL;
  return eng->error;
}

/****************************************
 * round_script_engine_lock
 ****************************************/

bool round_script_engine_lock(RoundScriptEngine *eng) {
  if (!eng)
    return false;
  return round_mutex_lock(eng->mutex);
}

/****************************************
 * round_script_engine_unlock
 ****************************************/

bool round_script_engine_unlock(RoundScriptEngine *eng) {
  if (!eng)
    return false;
  return round_mutex_unlock(eng->mutex);
}
