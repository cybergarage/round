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
#include <round/rpc_server.h>
#include <round/error_internal.h>
#include <round/node_internal.h>
#include <round/util/strings.h>
#include <round/util/json.h>

void round_rpc_server_jsonrpcrequestrecieved(mUpnpHttpRequest *httpReq);

/****************************************
* round_rpc_server_new
****************************************/

RoundRpcServer *round_rpc_server_new(void)
{
  RoundRpcServer *server;

  server = (RoundRpcServer *)malloc(sizeof(RoundRpcServer));

  if (!server)
    return NULL;

  server->upnpServer = round_upnp_server_new();
  
  if (!server->upnpServer) {
    round_rpc_server_delete(server);
    return NULL;
  }

  round_upnp_server_setrpcserver(server->upnpServer, server);
  round_upnp_server_setrpcrequestlistener(server->upnpServer, round_rpc_server_jsonrpcrequestrecieved);
  
  return server;
}

/****************************************
* round_rpc_server_delete
****************************************/

bool round_rpc_server_delete(RoundRpcServer *server)
{
  if (!server)
    return false;

  if (!round_rpc_server_stop(server))
    return false;
  
  round_upnp_server_delete(server->upnpServer);
  
  free(server);
  
  return true;
}

/****************************************
 * round_rpc_server_start
 ****************************************/

bool round_rpc_server_start(RoundRpcServer *server)
{
  bool isSuccess = true;
  
  if (!server)
    return false;

  isSuccess &= round_upnp_server_start(server->upnpServer);
  
  if (!isSuccess) {
    round_rpc_server_stop(server);
    return false;
  }
  
  return true;
}

/****************************************
 * round_rpc_server_stop
 ****************************************/

bool round_rpc_server_stop(RoundRpcServer *server)
{
  bool isSuccess = true;

  if (!server)
    return false;
  
  isSuccess &= round_upnp_server_stop(server->upnpServer);
  
  return true;
}

/****************************************
 * round_rpc_server_isrunning
 ****************************************/

bool round_rpc_server_isrunning(RoundRpcServer *server)
{
  if (!server)
    return false;
  
  if (!round_upnp_server_isrunning(server->upnpServer))
    return false;

  return true;
}

/****************************************
 * round_rpc_server_hasjsonrpcparameters
 ****************************************/

bool round_rpc_server_hasjsonrpcparameters(RoundJSON *json)
{
  RoundJSONObject *rootObj = round_json_getrootobject(json);
  if (!rootObj)
    return false;
  
  if (!round_json_object_isarray(rootObj))
    return false;
  
  return true;
}

/****************************************
 * round_rpc_server_jsonrpcrequestrecieved
 ****************************************/

void round_rpc_server_postresponse(mUpnpHttpRequest *httpReq, RoundJSONObject *jsonObj)
{
  mUpnpHttpResponse *httpRes = mupnp_http_response_new();
  if (!httpRes)
    return;
  
  mupnp_http_response_setstatuscode(httpRes, ROUNDC_RPC_HTTP_STATUS_CODE_OK);

  const char *jsonContent = NULL;
  round_json_object_tostring(jsonObj, RoundJSONOptionNone, &jsonContent);
  if (jsonContent) {
    mupnp_http_response_setcontent(httpRes, jsonContent);
  }
  
  mupnp_http_request_postresponse(httpReq, httpRes);
  mupnp_http_response_delete(httpRes);
}

/****************************************
 * round_rpc_server_jsonrpcrequestrecieved
 ****************************************/

void round_rpc_server_posterrorresponse(mUpnpHttpRequest *httpReq, int rpcErrCode)
{
  mUpnpHttpResponse *httpRes = mupnp_http_response_new();
  mupnp_http_response_setstatuscode(httpRes, round_json_rpc_errorcode2httpstatuscode(rpcErrCode));
  
  // TODO : Set JSON response content
  //RoundError *err = round_error_new();
  //round_error_setjsonrpcerrorcode(err, rpcErrCode);
  
  mupnp_http_request_postresponse(httpReq, httpRes);
  mupnp_http_response_delete(httpRes);
}

/****************************************
 * round_rpc_server_jsonrpcrequestrecieved
 ****************************************/

void round_rpc_server_jsonrpcrequestrecieved(mUpnpHttpRequest *httpReq)
{
  // Check content
  
  const char *jsonContent = mupnp_http_request_getcontent(httpReq);
  if (jsonContent) {
    round_rpc_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_INVALID_REQUEST);
    return;
  }

  // Get local node
  
  mUpnpDevice *upnpDev = (mUpnpDevice *)mupnp_http_request_getuserdata(httpReq);
  if (!upnpDev) {
    round_rpc_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return;
  }
  
  RoundRpcServer *rpcServer = round_upnp_device_getrpcserver(upnpDev);
  if (!rpcServer) {
    round_rpc_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return;
  }

  RoundLocalNode *node = round_rpc_server_getlocalnode(rpcServer);
  if (!node) {
    round_rpc_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return;
  }

  // Exec Message
  
  RoundMessage *msg = round_message_new();
  if (!msg) {
    round_rpc_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return;
  }
  round_message_setstring(msg, jsonContent);
  
  RoundError *err = round_error_new();
  if (!err) {
    round_rpc_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    round_message_delete(msg);
    return;
  }
  
  RoundJSONObject *resObj = NULL;
  
  if (round_local_node_execmessage(node, msg, &resObj, err)) {
    round_rpc_server_postresponse(httpReq, resObj);
  }
  else {
    round_rpc_server_posterrorresponse(httpReq, round_error_getdetailcode(err));
  }

  if (resObj) {
    round_json_object_delete(resObj);
  }
  
  round_error_delete(err);
  round_message_delete(msg);
}

