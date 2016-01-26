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
#include <round/script/lua.h>

#if defined(ROUND_SUPPORT_LUA)

// FIXME : Update not to use the global variable
static RoundLocalNode* gRoundLuaEnginenode = NULL;

/****************************************
 * round_lua_setlocalnode
 ****************************************/

void round_lua_setlocalnode(RoundLocalNode* node)
{
  gRoundLuaEnginenode = node;
}

/****************************************
 * round_lua_getlocalnode
 ****************************************/

RoundLocalNode* round_lua_getlocalnode()
{
  return gRoundLuaEnginenode;
}

/****************************************
 * round_lua_getnetworkstate
 ****************************************/

int round_lua_getnetworkstate(lua_State* L)
{
  /*
  const char * json = "";

  RoundLocalNode* node = round_lua_getlocalnode();
  if (node) {
    RoundLocalNodeResponse nodeRes;
    Round::SystemGetNetworkInfoResponse sysRes(&nodeRes);
    if (sysRes.setClusters(node)) {
      nodeRes.getResult(&json);
    }
  }

  lua_pushstring(L, json.c_str());
   */
  
  return 1;
}

/****************************************
 * round_lua_getclusterstate
 ****************************************/

int round_lua_getclusterstate(lua_State* L)
{
  /*
  const char * json = "";

  RoundLocalNode* node = round_lua_getlocalnode();
  if (node) {
    RoundLocalNodeResponse nodeRes;
    Round::SystemGetClusterInfoResponse sysRes(&nodeRes);
    if (sysRes.setCluster(node)) {
      nodeRes.getResult(&json);
    }
  }

  lua_pushstring(L, json.c_str());
  */

  return 1;
}

/****************************************
 * round_lua_getlocalnodestate
 ****************************************/

int round_lua_getlocalnodestate(lua_State* L)
{
  /*
  const char * json = "";

  RoundLocalNode* node = round_lua_getlocalnode();
  if (node) {
    RoundLocalNodeResponse nodeRes;
    Round::SystemGetNodeInfoResponse sysRes(&nodeRes);
    if (sysRes.setNode(node)) {
      nodeRes.getResult(&json);
    }
  }

  lua_pushstring(L, json.c_str());
  */

  return 1;
}

/****************************************
 * round_lua_setregistry
 ****************************************/

int round_lua_setregistry(lua_State* L)
{
  RoundLocalNode* node = round_lua_getlocalnode();
  const char * key = luaL_checkstring(L, 1);
  const char * val = luaL_checkstring(L, 2);

  bool isSuccess = false;
  if (node && key && val) {
    isSuccess = round_local_node_setregistry(node, key, val);
  }

  lua_pushboolean(L, isSuccess);

  return 1;
}

/****************************************
 * round_lua_getregistry
 ****************************************/

int round_lua_getregistry(lua_State* L)
{
  bool isSuccess = false;
  const char * result = "";

  RoundLocalNode* node = round_lua_getlocalnode();
  const char * key = luaL_checkstring(L, 1);
  if (node && key) {
    RoundRegistry *reg = round_local_node_getregistry(node, key);
    if (reg) {
      result = round_registry_getvalue(reg);
    }
  }

  lua_pushboolean(L, isSuccess);
  lua_pushstring(L, result );

  return 2;
}

/****************************************
 * round_lua_removeregistry
 ****************************************/

int round_lua_removeregistry(lua_State* L)
{
  bool isSuccess = false;

  RoundLocalNode* node = round_lua_getlocalnode();
  const char * key = luaL_checkstring(L, 1);
  if (node && key) {
    isSuccess = round_local_node_removeregistry(node, key);
  }

  lua_pushboolean(L, isSuccess);

  return 1;
}

/****************************************
 * round_lua_postmethod
 ****************************************/

int round_lua_postmethod(lua_State* L)
{
  bool isSuccess = false;
  const char * result = "";

  const char * method = luaL_checkstring(L, 1);
  const char * params = luaL_checkstring(L, 2);
  const char * dest = luaL_checkstring(L, 3);

  RoundJSONObject *resObj;
  RoundError err;

  RoundLocalNode* node = round_lua_getlocalnode();
  if (node && method && params && dest) {
    round_error_init(&err);
    if (round_local_node_postmethod(node, method, params, &resObj, &err)) {
      round_json_object_tostring(resObj, &result);
    }
    round_error_destroy(&err);
  }

  lua_pushboolean(L, isSuccess);
  lua_pushstring(L, result);

  if (resObj) {
    round_json_object_delete(resObj);
  }
  
  return 2;
}

#endif
