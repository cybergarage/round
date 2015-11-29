/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/const.h>
#include <round/error_internal.h>

/****************************************
 * round_json_rpc_errorcode2httpstatuscode
 ****************************************/

int round_json_rpc_errorcode2httpstatuscode(int rpcErrCode)
{
  // Standard Response Error Codes
  switch (rpcErrCode) {
    case ROUND_RPC_ERROR_CODE_PARSER_ERROR:
    case ROUND_RPC_ERROR_CODE_INVALID_PARAMS:
    case ROUND_RPC_ERROR_CODE_INTERNAL_ERROR:
      return ROUND_RPC_HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR;
    case ROUND_RPC_ERROR_CODE_INVALID_REQUEST:
      return ROUND_RPC_HTTP_STATUS_CODE_BAD_REQUEST;
    case ROUND_RPC_ERROR_CODE_METHOD_NOT_FOUND:
      return ROUND_RPC_HTTP_STATUS_CODE_NOT_FOUND;
  }
  
  // Extended Parameter Error Codes
  switch (rpcErrCode) {
    case ROUND_RPC_ERROR_CODE_BAD_DESTINATION:
      return ROUND_RPC_HTTP_STATUS_CODE_BAD_REQUEST;
    case ROUND_RPC_ERROR_CODE_MOVED_PERMANENTLY:
      return ROUND_RPC_HTTP_STATUS_CODE_MOVED_PERMANENTLY;
  }
  
  // Extented Parameter
  switch (rpcErrCode) {
    case ROUND_RPC_ERROR_CODE_CONDITION_FAILED:
      return ROUND_RPC_HTTP_STATUS_CODE_NOT_ACCEPTABLE;
  }
  
  // Extended Script Engine Error Codes
  switch (rpcErrCode) {
    case ROUND_RPC_ERROR_CODE_SCRIPT_ENGINE_INTERNAL_ERROR:
    case ROUND_RPC_ERROR_CODE_SCRIPT_COMPILE_ERROR:
    case ROUND_RPC_ERROR_CODE_SCRIPT_RUNTIME_ERROR:
      return ROUND_RPC_HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR;
    case ROUND_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND:
      return ROUND_RPC_HTTP_STATUS_CODE_BAD_REQUEST;
  }
  
  return ROUND_RPC_HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR;
}

/****************************************
 * round_json_rpc_errorcode2string
 ****************************************/

const char *round_json_rpc_errorcode2string(int rpcErrCode)
{
  switch (rpcErrCode) {
    case ROUND_RPC_ERROR_CODE_PARSER_ERROR:
      return ROUND_RPC_ERROR_CODE_PARSER_ERROR_MSG;
    case ROUND_RPC_ERROR_CODE_INVALID_REQUEST:
      return ROUND_RPC_ERROR_CODE_INVALID_REQUEST_MSG;
    case ROUND_RPC_ERROR_CODE_METHOD_NOT_FOUND:
      return ROUND_RPC_ERROR_CODE_METHOD_NOT_FOUND_MSG;
    case ROUND_RPC_ERROR_CODE_INVALID_PARAMS:
      return ROUND_RPC_ERROR_CODE_INVALID_PARAMS_MSG;
    case ROUND_RPC_ERROR_CODE_INTERNAL_ERROR:
      return ROUND_RPC_ERROR_CODE_INTERNAL_ERROR_MSG;
    case ROUND_RPC_ERROR_CODE_BAD_DESTINATION:
      return ROUND_RPC_ERROR_CODE_BAD_DESTINATION_MSG;
    case ROUND_RPC_ERROR_CODE_MOVED_PERMANENTLY:
      return ROUND_RPC_ERROR_CODE_MOVED_PERMANENTLY_MSG;
    case ROUND_RPC_ERROR_CODE_CONDITION_FAILED:
      return ROUND_RPC_ERROR_CODE_CONDITION_FAILED_MSG;
    case ROUND_RPC_ERROR_CODE_SCRIPT_ENGINE_INTERNAL_ERROR:
      return ROUND_RPC_ERROR_CODE_SCRIPT_ENGINE_INTERNAL_ERROR_MSG;
    case ROUND_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND:
      return ROUND_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND_MSG;
    case ROUND_RPC_ERROR_CODE_SCRIPT_COMPILE_ERROR:
      return ROUND_RPC_ERROR_CODE_SCRIPT_COMPILE_ERROR_MSG;
    case ROUND_RPC_ERROR_CODE_SCRIPT_RUNTIME_ERROR:
      return ROUND_RPC_ERROR_CODE_SCRIPT_RUNTIME_ERROR_MSG;
  }
  
  return ROUND_RPC_ERROR_CODE_UNKNOWN_MSG;
}

/****************************************
 * round_error_setjsonrpcerrorcode
 ****************************************/

bool round_error_setjsonrpcerrorcode(RoundError *err, int rpcErrCode)
{
  int httpStatusCode;
  
  if (!err)
    return false;
  
  httpStatusCode = round_json_rpc_errorcode2httpstatuscode(rpcErrCode);
  round_error_setcode(err, httpStatusCode);
  
  round_error_setdetailcode(err, rpcErrCode);
  round_error_setdetailmessage(err, round_json_rpc_errorcode2string(rpcErrCode));

  return true;
}
