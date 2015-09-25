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
 * round_local_node_execmethod
 ****************************************/

bool round_local_node_execmethod(RoundLocalNode *node, const char *name, const char *param, RoundString *result, RoundError *err)
{
  if (!node)
    return false;
  
  return round_method_manager_execmethod(node->methodMgr, name, param, result, err);
}

