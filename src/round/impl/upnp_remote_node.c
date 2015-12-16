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
#include <mupnp/http/http.h>

/****************************************
 * round_remote_node_posthttpjsonrequest
 ****************************************/

bool round_remote_node_posthttpjsonrequest(RoundRemoteNode* node, const char* reqContent, RoundJSONObject** resObj, RoundError* err)
{
  const char* remoteAddr = NULL;
  int remotePort = 0;
  if (!round_remote_node_getaddress(node, &remoteAddr) || !round_remote_node_getport(node, &remotePort)) {
    round_node_rpcerrorcode2error(node, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR, err);
    return false;
  }

  mUpnpHttpRequest* httpReq = mupnp_http_request_new();
  if (!httpReq) {
    round_node_rpcerrorcode2error(node, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR, err);
    return false;
  }

  mupnp_http_request_setmethod(httpReq, MUPNP_HTTP_POST);
  mupnp_http_request_seturi(httpReq, ROUND_RPC_HTTP_ENDPOINT);
  mupnp_http_request_setcontent(httpReq, reqContent);
  mupnp_http_request_setcontentlength(httpReq, mupnp_strlen(reqContent));

  mUpnpHttpResponse* httpRes = mupnp_http_request_post(httpReq, remoteAddr, remotePort);
  if (!httpRes) {
    round_node_rpcerrorcode2error(node, ROUND_RPC_ERROR_CODE_BAD_DESTINATION, err);
    mupnp_http_request_delete(httpReq);
    return false;
  }

  const char* resContent = mupnp_http_response_getcontent(httpRes);
  if (round_strlen(resContent) <= 0) {
    round_node_rpcerrorcode2error(node, ROUND_RPC_ERROR_CODE_BAD_DESTINATION, err);
    mupnp_http_request_delete(httpReq);
    return false;
  }

  // Set JSON Response
  
  RoundJSON* json = round_json_new();
  if (!json) {
    round_node_rpcerrorcode2error(node, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR, err);
    mupnp_http_request_delete(httpReq);
  }

  *resObj = NULL;
  if (round_json_parse(json, resContent, err)) {
    *resObj = round_json_poprootobject(json);
  }
  
  round_json_delete(json);

  // Set Error Response
  
  if (!mupnp_http_response_issuccessful(httpRes)) {
    if (*resObj) {
      RoundJSONObject *errObj;
      if (round_json_rpc_geterror(*resObj, &errObj)) {
        round_error_setjsonrpcerror(err, errObj);
      }
    }
  }
  
  return true;
}
