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

#include <round/script/native.h>
#include <round/script/js.h>
#include <round/script/lua.h>
#include <round/script/ruby.h>
#include <round/method/system_method.h>

/****************************************
* round_local_node_new
****************************************/

RoundLocalNode *round_local_node_new(void)
{
  RoundLocalNode *node;

  node = (RoundLocalNode *)malloc(sizeof(RoundLocalNode));

  if (!node)
    return NULL;

  if (!round_local_node_init(node)) {
    round_local_node_delete(node);
    return NULL;
  }
  
  return node;
}

/****************************************
 * round_local_node_init
 ****************************************/

bool round_local_node_init(RoundLocalNode *node)
{
  round_node_init((RoundNode *)node);
  round_oo_setdescendantdestoroyfunc(node, round_local_node_destory);
  
  node->methodMgr = round_method_manager_new();
  node->regMgr = round_registry_manager_new();
  node->threadMgr = round_thread_manager_new();

  if (!node->methodMgr || !node->regMgr || !node->threadMgr)
    return false;

  round_node_setpostmessagefunc(node, round_local_node_postmessage);
  
  if (!round_local_node_initthreads(node))
    return false;

  if (!round_local_node_initscriptengines(node))
    return false;
  
  if (!round_local_node_initsystemmethods(node))
    return false;

  return true;
}

/****************************************
 * round_local_node_initthreads
 ****************************************/

bool round_local_node_initthreads(RoundLocalNode *node)
{
  RoundThreadFunc threadFuncs[] = {round_local_node_message_thread};
  RoundThread *thread;
  size_t n, threadFuncCnt;
  
  threadFuncCnt = sizeof(threadFuncs) / sizeof(RoundThreadFunc);
  for (n=0; n<threadFuncCnt; n++) {
    thread = round_thread_new();
    if (!thread)
      return false;
    round_thread_setuserdata(thread, node);
    round_thread_setaction(thread, threadFuncs[n]);
    if (!round_thread_manager_add(node->threadMgr, thread))
      return false;
  }
  
  return true;
}

/****************************************
 * round_local_node_initscriptengines
 ****************************************/

bool round_local_node_initscriptengines(RoundLocalNode *node)
{
  bool areAllEnginesAdded;
  
  areAllEnginesAdded = true;
  
  areAllEnginesAdded &= round_local_node_addengine(node, (RoundScriptEngine *)round_native_engine_new());
  
#if defined(ROUND_SUPPORT_JS_SM)
  areAllEnginesAdded &= round_local_node_addengine(node, (RoundScriptEngine *)round_js_engine_new());
#endif
  
#if defined(ROUND_SUPPORT_LUA)
  areAllEnginesAdded &= round_local_node_addengine(node, (RoundScriptEngine *)round_lua_engine_new());
#endif
  
#if defined(ROUND_SUPPORT_RUBY)
  areAllEnginesAdded &= round_local_node_addengine(node, (RoundScriptEngine *)round_ruby_engine_new());
#endif
  
  return areAllEnginesAdded;
}

/****************************************
 * round_local_node_initsystemmethods
 ****************************************/

bool round_local_node_initsystemmethods(RoundLocalNode *node)
{
  bool areAllMethodsAdded;
  
  areAllMethodsAdded = true;
  
  areAllMethodsAdded &= round_local_node_setmethod(node, round_system_method_setmethod_new());
  areAllMethodsAdded &= round_local_node_setmethod(node, round_system_method_removemethod_new());
  
  areAllMethodsAdded &= round_local_node_setmethod(node, round_system_method_setregistry_new());
  areAllMethodsAdded &= round_local_node_setmethod(node, round_system_method_getregistry_new());
  areAllMethodsAdded &= round_local_node_setmethod(node, round_system_method_removeregistry_new());

  return areAllMethodsAdded;
}

/****************************************
 * round_local_node_destory
 ****************************************/

bool round_local_node_destory(RoundLocalNode *node)
{
  if (!node)
    return false;
  
  if (!round_local_node_stop(node))
    return false;
  
  round_method_manager_delete(node->methodMgr);
  round_registry_manager_delete(node->regMgr);
  round_thread_manager_delete(node->threadMgr);

  return true;
}

/****************************************
* round_local_node_delete
****************************************/

bool round_local_node_delete(RoundLocalNode *node)
{
  if (!node)
    return false;
  
  if (!round_local_node_destory(node))
    return false;
  
  round_node_destroy((RoundNode *)node);

  free(node);
  
  return true;
}

/****************************************
 * round_local_node_start
 ****************************************/

bool round_local_node_start(RoundLocalNode *node)
{
  bool isSuccess = true;
  
  if (!node)
    return false;

  isSuccess &= round_thread_manager_start(node->threadMgr);
  
  if (!isSuccess) {
    round_local_node_stop(node);
    return false;
  }

  return true;
}

/****************************************
 * round_local_node_stop
 ****************************************/

bool round_local_node_stop(RoundLocalNode *node)
{
  bool isSuccess = true;
  
  if (!node)
    return false;

  isSuccess &= round_thread_manager_stop(node->threadMgr);

  return isSuccess;
}

/****************************************
 * round_local_node_isrunning
 ****************************************/

bool round_local_node_isrunning(RoundLocalNode *node)
{
  if (!node)
    return false;

  if (!round_thread_manager_isrunning(node->threadMgr))
    return false;

  return true;
}

/****************************************
 * round_local_node_setmethod
 ****************************************/

bool round_local_node_setmethod(RoundLocalNode *node, RoundMethod *method)
{
  const char *methodName;
  RoundMethod *exMethod;
  
  if (!node)
    return false;
  
  methodName = round_method_getname(method);
  
  exMethod = round_method_manager_getmethod(node->methodMgr, methodName);
  if (exMethod) {
    if (round_method_isfinal(exMethod))
      return false;
    round_method_manager_removemethod(node->methodMgr, methodName);
  }

  if (!round_method_manager_addmethod(node->methodMgr, method))
    return false;
  
  return true;
}

/****************************************
 * round_local_node_removemethod
 ****************************************/

bool round_local_node_removemethod(RoundLocalNode *node, const char *name)
{
  RoundMethod *method;
  
  if (!node)
    return false;
  
  method = round_method_manager_getmethod(node->methodMgr, name);
  if (!method)
    return false;
  
  if (round_method_isfinal(method))
    return false;
  
  return round_method_manager_removemethod(node->methodMgr, name);
}

/****************************************
 * round_local_node_isfinalmethod
 ****************************************/

bool round_local_node_isfinalmethod(RoundLocalNode *node, const char *name)
{
  RoundMethod *method;
  
  if (!node)
    return false;
  
  method = round_method_manager_getmethod(node->methodMgr, name);
  if (!method)
    return false;
  
  return round_method_isfinal(method);
}

/****************************************
 * round_local_node_addengine
 ****************************************/

bool round_local_node_addengine(RoundLocalNode *node, RoundScriptEngine *engine)
{
  if (!node)
    return false;
  
  if (!round_method_manager_addengine(node->methodMgr, engine))
    return false;
  
  round_script_engine_setlocalnode(engine, node);

  return true;
}

/****************************************
 * round_local_node_setregistry
 ****************************************/

bool round_local_node_setregistry(RoundLocalNode *node, const char *key, const char *val)
{
  RoundRegistry *reg;
  
  if (!node)
    return false;

  reg = round_registry_manager_get(node->regMgr, key);
  if (!reg) {
    reg = round_registry_new();
    if (!reg)
      return false;
    if (round_registry_manager_set(node->regMgr, reg)) {
      round_registry_delete(reg);
      return false;
    }
    round_registry_setkey(reg, key);
  }

  round_registry_setvalue(reg, val);
  round_registry_setts(reg, time(NULL));
  round_registry_setlts(reg, round_node_getclockvalue(node));
  
  return true;
}

/****************************************
 * round_local_node_getregistry
 ****************************************/

RoundRegistry *round_local_node_getregistry(RoundLocalNode *node, const char *key)
{
  if (!node)
    return false;

  return round_registry_manager_get(node->regMgr, key);
}

/****************************************
 * round_local_node_removeregistry
 ****************************************/

bool round_local_node_removeregistry(RoundLocalNode *node, const char *key)
{
  if (!node)
    return false;
  
  return round_registry_manager_remove(node->regMgr, key);
}

/****************************************
 * round_local_node_postmessage
 ****************************************/

bool round_local_node_postmessage(RoundLocalNode *node, RoundJSONObject *reqMap, RoundJSONObject *resMap, RoundError *err)
{
  const char *msgId, *method, *params;
  long ts;
  bool isSuccess;
  RoundJSONObject *jsonResult;

  if (!node) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  
  // Check request
  
  if (!round_json_object_ismap(reqMap)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INVALID_REQUEST);
    return false;
  }
  
  // Set id and ts parameter
  
  if (round_json_rpc_getid(reqMap, &msgId)) {
    round_json_rpc_setid(resMap, msgId);
  }
  round_json_rpc_settimestamp(resMap, round_node_getclockvalue(node));

  // Updated local clock
  
  if (round_json_rpc_gettimestamp(reqMap, &ts)) {
    round_node_setremoteclockvalue(node, ts);
  }
  else {
    round_node_incrementclock(node);
  }

  /*
   // Check dest
   
   if (!nodeReq->isDestValid()) {
   setError(RPC::JSON::ErrorCodeInvalidParams, error);
   return false;
   }
   
   bool isDestHash = nodeReq->isDestHash();
   if (isDestHash) {
   std::string nodeHash;
   if (nodeReq->getDest(&nodeHash)) {
   NodeGraph *nodeGraph = getNodeGraph();
   if (!nodeGraph->isHandleNode(this, nodeHash)) {
   setError(RPC::JSON::ErrorCodeMovedPermanently, error);
   return false;
   }
   }
   }
   
   // Exec Method (One node)
   
   bool isDestOne = nodeReq->isDestOne();
   if (isDestOne) {
   return execMethod(nodeReq, nodeRes, error);
   }
   
   // Exec Method (Multi node)
   
   JSONArray *batchArray = new JSONArray();
   nodeRes->setResult(batchArray);
   
   Error thisNodeError;
   NodeResponse *thisNodeRes = new NodeResponse();
   execMethod(nodeReq, thisNodeRes, &thisNodeError);
   thisNodeRes->setDest(this);
   batchArray->add(thisNodeRes);
   
   NodeList otherNodes;
   if (nodeReq->isDestAll()) {
   getAllOtherNodes(&otherNodes);
   }
   else if (nodeReq->hasQuorum()) {
   size_t quorum;
   if (nodeReq->getQuorum(&quorum)) {
   getQuorumNodes(&otherNodes, quorum);
   }
   }
   for (NodeList::iterator node = otherNodes.begin(); node != otherNodes.end(); node++) {
   Error otherNodeError;
   NodeResponse *otherNodeRes = new NodeResponse();
   (*node)->postMessage(nodeReq, otherNodeRes, &otherNodeError);
   otherNodeRes->setDest((*node));
   batchArray->add(otherNodeRes);
   }
   */
  
  // Exec Message
  
  if (round_json_rpc_getmethod(reqMap, &method) && (0 < round_strlen(method))) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_METHOD_NOT_FOUND);
    return false;
  }

  round_json_rpc_getparams(reqMap, &params);
  jsonResult = NULL;
  isSuccess = round_method_manager_execmethod(node->methodMgr, method, params, &jsonResult, err);

  if (isSuccess) {
    if (jsonResult) {
      round_json_rpc_setresult(resMap, jsonResult);
      round_json_object_delete(jsonResult);
    }
  }

/*
  bool isMethodExecuted = false;
  bool isMethodSuccess = false;
  
  if (isAliasMethod(name)) {
    isMethodExecuted = true;
    isMethodSuccess = execAliasMethod(nodeReq, nodeRes, error);
  }
  
  if (!isMethodExecuted) {
    setError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  if (!isMethodSuccess)
    return false;
  
  if (!hasRoute(name)) {
    return true;
  }
  
  NodeResponse routeNodeRes;
  if (!execRoute(name, nodeRes, &routeNodeRes, error)) {
    return false;
  }
  
  nodeRes->set(&routeNodeRes);
*/

  return isSuccess;
}

/****************************************
 * round_local_node_seterrorresponse
 ****************************************/

bool round_local_node_seterrorresponse(RoundLocalNode *node, int rpcErrCode, RoundError *err, RoundJSONObject **resObj)
{
  if (!node)
    return false;
  
  if (err) {
    round_error_setjsonrpcerrorcode(err, rpcErrCode);
  }
  
  *resObj = round_json_map_new();
  round_json_rpc_seterror(*resObj, err);
  
  return true;
}

/****************************************
 * round_local_node_execmessage
 ****************************************/

bool round_local_node_execmessage(RoundLocalNode *node, RoundMessage *msg, RoundJSONObject **resObj, RoundError *err)
{
  RoundJSON *json;
  const char *msgContent;
  RoundJSONObject *reqObj, *msgArrayObj, *resArrayObj;
  size_t n, msgArrayCnt;
  
  if (!node || !msg || !resObj || !err)
    return round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
  
  // Parse JSON-RPC request
  
  msgContent = round_message_getstring(msg);
  if (!msgContent)
    return round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INVALID_REQUEST, err, resObj);
  
  json = round_json_new();
  if (!json)
    return round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);

  if (!round_json_parse(json, msgContent, err)) {
    round_json_delete(json);
    return round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INVALID_REQUEST, err, resObj);
  }

  // Check JSON-RPC request
  
  reqObj = round_json_getrootobject(json);
  if (!reqObj) {
    round_json_delete(json);
    return round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
  }

  if (!round_json_object_ismap(reqObj) && !round_json_object_isarray(reqObj)) {
    round_json_delete(json);
    return round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INVALID_REQUEST, err, resObj);
  }
  
  // Single request
  
  if (round_json_object_ismap(reqObj)) {
    *resObj = round_json_map_new();
    if (!round_local_node_postmessage(node, reqObj, *resObj, err)) {
      round_json_rpc_seterror(*resObj, err);
    }
    return true;
  }
  
  // Batch request
  
  if (round_json_object_isarray(reqObj)) {
    *resObj = round_json_array_new();
    msgArrayCnt = round_json_array_size(reqObj);
    for (n=0; n<msgArrayCnt; n++) {
      msgArrayObj = round_json_array_get(reqObj, n);
      resArrayObj = round_json_map_new();
      if (!round_local_node_postmessage(node, reqObj, resArrayObj, err)) {
        round_json_rpc_seterror(resArrayObj, err);
      }
      round_json_array_append(*resObj, resArrayObj);
    }
    return true;
  }

  return round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
}

/****************************************
 * round_local_node_postrequest
 ****************************************/

bool round_local_node_postrequest(RoundLocalNode *node, RoundMessage *msg, RoundJSONObject **resObj, RoundError *err)
{
  if (!msg) {
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS, err, resObj);
    return false;
  }
  
  if (!node) {
    round_message_delete(msg);
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
    return false;
  }
  
  if (!resObj || !err) {
    round_message_delete(msg);
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS, err, resObj);
    return false;
  }
  
  if (!round_message_setnotifyenabled(msg, true)) {
    round_message_delete(msg);
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
    return false;
  }
  
  round_local_node_message_seterror(msg, err);
  round_local_node_message_setresponsejsonobject(msg, resObj);
  
  if (!round_message_manager_pushmessage(node->msgMgr, msg)) {
    round_message_delete(msg);
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
    return false;
  }
  
  if (!round_message_timedwaitnotify(msg, round_local_node_getrequesttimeout(node))) {
    round_message_setnotifyenabled(msg, false);
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
    return false;
  }
  
  return true;
}

/****************************************
 * round_local_node_postjsonrequest
 ****************************************/

bool round_local_node_postjsonrequest(RoundLocalNode *node, RoundJSONObject *reqObj, RoundJSONObject **resObj, RoundError *err)
{
  RoundMessage *msg;
  const char *reqStr;
  
  if (!node) {
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
    return false;
  }

  if (!reqObj || !resObj || !err) {
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS, err, resObj);
    return false;
  }

  reqStr = NULL;
  if (!round_json_object_tocompactstring(reqObj, &reqStr) || (0 < round_strlen(reqStr))) {
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INVALID_PARAMS, err, resObj);
    return false;
  }
  
  msg = round_local_node_message_new();
  if (!msg) {
    round_local_node_seterrorresponse(node, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR, err, resObj);
    return false;
  }
  round_message_setstring(msg, reqStr);

  return round_local_node_postrequest(node, msg, resObj, err);
}
