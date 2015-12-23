/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/node_internal.h>
#include <round/script/js.h>

#if defined(ROUND_SUPPORT_JS_SM)

#define ROUND_SCRIPT_JS_SM_MESSAGE_MAX 512
#define ROUND_SCRIPT_JS_SM_REGISTRY_KEY_MAX 128
#define ROUND_SCRIPT_JS_SM_REGISTRY_VALUE_MAX 1024

static RoundLocalNode* gRoundSpiderMonkeyEngineLocalNode = NULL;

/****************************************
 * round_js_sm_setlocalnode
 ****************************************/

void round_js_sm_setlocalnode(void* node)
{
  gRoundSpiderMonkeyEngineLocalNode = node;
}

/****************************************
 * round_js_sm_getlocalnode
 ****************************************/

void* round_js_sm_getlocalnode()
{
  return gRoundSpiderMonkeyEngineLocalNode;
}

/****************************************
 * JSSTRING_TO_STDSTRING
 ****************************************/

static bool JSSTRING_TO_STDSTRING(JSContext* cx, jsval* vp, size_t argn, char* buf, size_t bufSize)
{
  jsval* argv = JS_ARGV(cx, vp);

  jsval arg = argv[argn];
  if (!JSVAL_IS_STRING(arg))
    return false;

  JSString* jsStr = JSVAL_TO_STRING(arg);

  if (!jsStr)
    return false;

  size_t bufLen = JS_EncodeStringToBuffer(jsStr, buf, (bufSize - 1));
  buf[bufLen] = '\0';

  return true;
}

/****************************************
 * JSOBJECT_GET_GETPROPERTYSTRING
 ****************************************/

static bool JSOBJECT_GET_GETPROPERTY(JSContext* cx, jsval jsObj, const char *name, jsval *prop)
{
  if (JSVAL_IS_PRIMITIVE(jsObj))
    return false;
  
  if (!JSVAL_IS_OBJECT(jsObj))
    return false;
  
  if (JS_IsArrayObject(cx, JSVAL_TO_OBJECT(jsObj)))
    return true;
  
  if (!JS_GetProperty(cx, JSVAL_TO_OBJECT(jsObj), name, prop))
    return false;
  
  return true;
}

/****************************************
 * JSOBJECT_GET_GETPROPERTYSTRING
 ****************************************/

static bool JSOBJECT_GET_GETPROPERTYSTRING(JSContext* cx, jsval vp, const char *name, char* buf, size_t bufSize)
{
  jsval prop;
  if (!JSOBJECT_GET_GETPROPERTY(cx, vp, name, &prop))
    return false;
  
  if (!JSVAL_IS_PRIMITIVE(prop))
    return false;
  
  if (JSVAL_IS_VOID(prop))
    return false;
  
  if (!JSVAL_IS_STRING(prop))
    return false;
  
  JSString* jsStr = JSVAL_TO_STRING(prop);
  
  if (!jsStr)
    return false;
  
  size_t bufLen = JS_EncodeStringToBuffer(jsStr, buf, (bufSize - 1));
  buf[bufLen] = '\0';
  
  return true;
}

/****************************************
 * JS_SET_STDSTRING_RVAL
 ****************************************/

static bool JS_SET_STDSTRING_RVAL(JSContext* cx, jsval* vp, const char* result)
{
  JSString* jsResult = JS_NewStringCopyZ(cx, result);
  JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsResult));
  return true;
}

/****************************************
 * JS_SET_NODERESPONSE_RVAL
 ****************************************/

static bool JS_SET_NODERESPONSE_RVAL(JSContext* cx, jsval* vp, RoundJSONObject* nodeRes)
{
  const char* result;
  if (!round_json_object_getstring(nodeRes, &result))
    return false;
  return JS_SET_STDSTRING_RVAL(cx, vp, result);
}

/****************************************
 * round_js_sm_print
 ****************************************/

JSBool round_js_sm_print(JSContext* cx, unsigned argc, jsval* vp)
{
  if (argc < 1)
    return JS_FALSE;

  JS_BeginRequest(cx);

  char msg[ROUND_SCRIPT_JS_SM_MESSAGE_MAX];
  if (JSSTRING_TO_STDSTRING(cx, vp, 0, msg, sizeof(msg))) {
    printf("%s\n", msg);
  }

  return JS_TRUE;
}

/****************************************
 * round_js_sm_getnetworkstate
 ****************************************/

JSBool round_js_sm_getnetworkstate(JSContext* cx, unsigned argc, jsval* vp)
{
  RoundLocalNode* node = round_js_sm_getlocalnode();
  if (!node)
    return JS_FALSE;

  JS_BeginRequest(cx);

  /*
  RoundLocalNodeResponse nodeRes;
  Round::SystemGetNetworkInfoResponse sysRes(&nodeRes);
  sysRes.setClusters(node);
  
  JS_SET_NODERESPONSE_RVAL(cx, vp, nodeRes);
*/

  JS_EndRequest(cx);

  return JS_TRUE;
}

/****************************************
 * round_js_sm_getclusterstate
 ****************************************/

JSBool round_js_sm_getclusterstate(JSContext* cx, unsigned argc, jsval* vp)
{
  RoundLocalNode* node = round_js_sm_getlocalnode();
  if (!node)
    return JS_FALSE;

  JS_BeginRequest(cx);

  /*
  RoundLocalNodeResponse nodeRes;
  Round::SystemGetClusterInfoResponse sysRes(&nodeRes);
  sysRes.setCluster(node);
  
  JS_SET_NODERESPONSE_RVAL(cx, vp, nodeRes);
  */

  JS_EndRequest(cx);

  return JS_TRUE;
}

/****************************************
 * round_js_sm_getnodestate
 ****************************************/

JSBool round_js_sm_getnodestate(JSContext* cx, unsigned argc, jsval* vp)
{
  RoundLocalNode* node = round_js_sm_getlocalnode();
  if (!node)
    return JS_FALSE;

  JS_BeginRequest(cx);

  /*
  RoundLocalNodeResponse nodeRes;
  Round::SystemGetNodeInfoResponse sysRes(&nodeRes);
  sysRes.setNode(node);
  
  JS_SET_NODERESPONSE_RVAL(cx, vp, nodeRes);
  */

  JS_EndRequest(cx);

  return JS_TRUE;
}

/****************************************
 * round_js_sm_postmethod
 ****************************************/

JSBool round_js_sm_postmethod(JSContext* cx, unsigned argc, jsval* vp)
{
  if (argc < 2)
    return JS_FALSE;

  RoundLocalNode* node = round_js_sm_getlocalnode();
  if (!node)
    return JS_FALSE;

  JS_BeginRequest(cx);

  /*
  std::string method, params, dest;
  JSSTRING_TO_STDSTRING(cx, vp, 0, &method);
  JSSTRING_TO_STDSTRING(cx, vp, 1, &params);
  if (3 <= argc) {
    JSSTRING_TO_STDSTRING(cx, vp, 2, &dest);
  }
  
  Round::Error error;
  std::string result;
  bool isSuccess = node->postMessage(dest, method, params, &result);
  
  if (isSuccess) {
    JS_SET_STDSTRING_RVAL(cx, vp, result);
  }
  else {
    JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JSBool(JS_FALSE)));
  }
  */

  JS_EndRequest(cx);

  return JS_TRUE;
}

/****************************************
 * round_js_sm_setregistry
 ****************************************/

JSBool round_js_sm_setregistry(JSContext* cx, unsigned argc, jsval* vp)
{
  if (argc < 1)
    return JS_FALSE;

  RoundLocalNode* node = round_js_sm_getlocalnode();
  if (!node)
    return JS_FALSE;

  JS_BeginRequest(cx);

  char key[ROUND_SCRIPT_JS_SM_REGISTRY_KEY_MAX];
  if (!JSOBJECT_GET_GETPROPERTYSTRING(cx, vp[0], ROUND_SYSTEM_METHOD_PARAM_KEY, key, sizeof(key)))
    return false;

  printf("%s", key);
  
  char val[ROUND_SCRIPT_JS_SM_REGISTRY_VALUE_MAX];
  if (!JSOBJECT_GET_GETPROPERTYSTRING(cx, vp[0], ROUND_SYSTEM_METHOD_PARAM_VALUE, val, sizeof(val)))
    return false;
  
  bool isSuccess = round_local_node_setregistry(node, key, val);

  JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(isSuccess));

  JS_EndRequest(cx);

  return JS_TRUE;
}

/****************************************
 * round_js_sm_getregistry
 ****************************************/

JSBool round_js_sm_getregistry(JSContext* cx, unsigned argc, jsval* vp)
{
  if (argc < 1)
    return JS_FALSE;

  RoundLocalNode* node = round_js_sm_getlocalnode();
  if (!node)
    return JS_FALSE;

  JS_BeginRequest(cx);

  char key[ROUND_SCRIPT_JS_SM_REGISTRY_KEY_MAX];
  JSSTRING_TO_STDSTRING(cx, vp, 0, key, sizeof(key));

  RoundRegistry* reg = round_local_node_getregistry(node, key);

  if (reg) {
    RoundJSONObject* map = round_json_map_new();
    if (map) {
      round_script_registry2json(reg, map);
      const char* result;
      if (round_json_object_tostring(map, &result)) {
        JS_SET_STDSTRING_RVAL(cx, vp, result);
      }
      round_json_object_delete(map);
    }
    else {
      JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JS_FALSE));
    }
  }
  else {
    JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JS_FALSE));
  }

  JS_EndRequest(cx);

  return JS_TRUE;
}

/****************************************
 * round_js_sm_removeregistry
 ****************************************/

JSBool round_js_sm_removeregistry(JSContext* cx, unsigned argc, jsval* vp)
{
  if (argc < 1)
    return JS_FALSE;

  RoundLocalNode* node = round_js_sm_getlocalnode();
  if (!node)
    return JS_FALSE;

  JS_BeginRequest(cx);

  char key[ROUND_SCRIPT_JS_SM_REGISTRY_KEY_MAX];
  JSSTRING_TO_STDSTRING(cx, vp, 0, key, sizeof(key));

  bool isSuccess = round_local_node_removeregistry(node, key);

  JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(isSuccess));

  JS_EndRequest(cx);

  return JS_TRUE;
}

#endif
