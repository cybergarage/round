/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/error_internal.h>
#include <string.h>

/****************************************
 * round_error_new
 ****************************************/

RoundError* round_error_new(void)
{
  RoundError* err;

  err = (RoundError*)malloc(sizeof(RoundError));

  if (!err)
    return NULL;

  if (!round_error_init(err)) {
    round_error_delete(err);
    return NULL;
  }

  return err;
}

/****************************************
 * round_error_init
 ****************************************/

bool round_error_init(RoundError *err)
{
  round_error_setcode(err, 0);
  round_error_setdetailcode(err, 0);
  
  err->msg = round_string_new();
  err->detailMsg = round_string_new();

  if (!err->msg || !err->detailMsg)
    return false;

  return true;
}

/****************************************
 * round_error_delete
 ****************************************/

bool round_error_delete(RoundError* err)
{
  if (!err)
    return false;

  if (err->msg) {
    round_string_delete(err->msg);
  }
  if (err->detailMsg) {
    round_string_delete(err->detailMsg);
  }
  
  free(err);

  return true;
}

/****************************************
 * round_error_clear
 ****************************************/

bool round_error_clear(RoundError* err)
{
  if (!err)
    return false;

  if (!err->msg || !err->detailMsg)
    return false;
  
  round_error_setcode(err, 0);
  round_error_setdetailcode(err, 0);

  round_string_clear(err->msg);
  round_string_clear(err->detailMsg);

  return true;
}

/****************************************
 * round_error_setcode
 ****************************************/

bool round_error_setcode(RoundError* err, int code)
{
  if (!err)
    return false;
  err->code = code;
  return true;
}

/****************************************
 * round_error_getcode
 ****************************************/

int round_error_getcode(RoundError* err)
{
  if (!err)
    return 0;
  return err->code;
}

/****************************************
 * round_error_setmessage
 ****************************************/

bool round_error_setmessage(RoundError* err, const char* msg)
{
  if (!err)
    return false;
  return round_string_setvalue(err->msg, msg);
}

/****************************************
 * round_error_getmessage
 ****************************************/

const char* round_error_getmessage(RoundError* err)
{
  if (!err)
    return NULL;
  return round_string_getvalue(err->msg);
}

/****************************************
 * round_error_setdetailcode
 ****************************************/

bool round_error_setdetailcode(RoundError* err, int code)
{
  if (!err)
    return false;
  err->detailCode = code;
  return true;
}

/****************************************
 * round_error_getdetailcode
 ****************************************/

int round_error_getdetailcode(RoundError* err)
{
  if (!err)
    return 0;
  return err->detailCode;
}

/****************************************
 * round_error_setdetailmessage
 ****************************************/

bool round_error_setdetailmessage(RoundError* err, const char* msg)
{
  if (!err)
    return false;
  return round_string_setvalue(err->detailMsg, msg);
}

/****************************************
 * round_error_getdetailmessage
 ****************************************/

const char* round_error_getdetailmessage(RoundError* err)
{
  if (!err)
    return NULL;
  return round_string_getvalue(err->detailMsg);
}
