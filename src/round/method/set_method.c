/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/method/system_method.h>
#include <round/util/base64.h>

/****************************************
 * round_system_method_setmethod
 ****************************************/

bool round_system_method_setmethod(RoundLocalNode* node, RoundJSONObject* params, RoundJSONObject** result, RoundError* err)
{
  if (!round_json_object_ismap(params)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  const char *name;
  if (!round_json_map_getstring(params, ROUND_SYSTEM_METHOD_PARAM_NAME, &name)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  const char *lang;
  if (!round_json_map_getstring(params, ROUND_SYSTEM_METHOD_PARAM_LANGUAGE, &lang)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  byte* code;
  if (!round_json_map_getstring(params, ROUND_SYSTEM_METHOD_PARAM_CODE, (const char**)&code)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  size_t codeLen = round_strlen((const char*)code);

  // Decode

  bool isEncoded = false;
  const char *encode;
  if (!round_json_map_getstring(params, ROUND_SYSTEM_METHOD_PARAM_ENCODE, &encode)) {
    // Base64
    if (round_streq(encode, ROUND_SYSTEM_METHOD_PARAM_BASE64)) {
      byte *decodedCode;
      size_t decordedSize = round_base64_decode((const char *)code, &decodedCode);
      if (decordedSize <= 0) {
        round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
        return false;
      }
      
      isEncoded = true;
      code = decodedCode;
      codeLen = decordedSize;
    }
  }

  RoundMethod *newMethod = round_method_new();
  if (!newMethod) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }

  round_method_setname(newMethod, name);
  round_method_setlanguage(newMethod, lang);
  round_method_setcode(newMethod, code, codeLen);

  bool isAdded = round_local_node_setmethod(node, newMethod);
  if (!isAdded) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    round_method_delete(newMethod);
  }

  if (isEncoded) {
    free(code);
  }
  
  return isAdded;
}
