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
  
  node->server = round_server_new();
  node->methodMgr = round_method_manager_new();
  node->regMgr = round_registry_manager_new();

  if (!node->server || !node->methodMgr || !node->regMgr)
    return false;
  
  if (!round_local_node_initscriptengines(node))
    return false;
  
  if (!round_local_node_initsystemmethods(node))
    return false;

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
  
  round_method_manager_delete(node->methodMgr);
  round_registry_manager_delete(node->regMgr);
  round_server_delete(node->server);

  return true;
}

/****************************************
* round_local_node_delete
****************************************/

bool round_local_node_delete(RoundLocalNode *node)
{
  if (!node)
    return false;
  
  round_local_node_destory(node);
  round_node_destroy((RoundNode *)node);

  free(node);
  
  return true;
}

/****************************************
 * round_local_node_start
 ****************************************/

bool round_local_node_start(RoundLocalNode *node)
{
  if (!node)
    return false;

  return true;
}

/****************************************
 * round_local_node_stop
 ****************************************/

bool round_local_node_stop(RoundLocalNode *node)
{
  if (!node)
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

bool round_local_node_postmessage(RoundNode *node, RoundJSONObject *reqObj, RoundJSONObject *resObj, RoundError *err)
{
  return true;
}

/****************************************
 * round_local_node_execmethod
 ****************************************/

bool round_local_node_execmethod(RoundLocalNode *node, RoundJSONObject *reqMap, RoundJSONObject *resMap, RoundError *err)
{
  const char *msgId, *method, *params;
  bool isSuccess;
  RoundJSONObject *jsonResult;

  if (!node) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  
  // Set id and ts parameter
  
  if (round_json_rpc_getid(reqMap, &msgId)) {
    round_json_rpc_setid(resMap, msgId);
  }
  round_json_rpc_settimestamp(resMap, round_node_getclockvalue(node));

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
  else {
    round_json_rpc_seterror(resMap, err);
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
 * round_local_node_execmessage
 ****************************************/

bool round_local_node_execmessage(RoundNode *node, RoundMessage *msg, RoundJSONObject *resObj, RoundError *err)
{
  RoundJSON *json;
  const char *msgContent;
  
  if (!node || !msg || !resObj || !err) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }
  
  msgContent = round_message_getstring(msg);
  if (!msgContent) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INVALID_REQUEST);
    return false;
  }
  
  json = round_json_new();
  if (!json) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }

  if (round_json_parse(json, msgContent, err)) {
    round_error_setjsonrpcerrorcode(err, ROUNDC_RPC_ERROR_CODE_INVALID_REQUEST);
    round_json_delete(json);
    return false;
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
   */
  // Update local clock
  
  /*
   clock_t remoteTs;
   if (nodeRes->getTimestamp(&remoteTs)) {
   setRemoteClock(remoteTs);
   }
   else {
   incrementLocalClock();
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
  
  return true;
}
