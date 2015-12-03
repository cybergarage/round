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

bool round_remote_node_posthttpjsonrequest(RoundRemoteNode* node, const char *reqContent, RoundJSONObject* resMap, RoundError* err)
{
  const char *remoteAddr = NULL;
  int remotePort = 0;
  if (!round_remote_node_getaddress(node, &remoteAddr) || !round_remote_node_getport(node, &remotePort)) {
    round_node_rpcerrorcode2error(node, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR, err);
    return false;
  }
  
  mUpnpHttpRequest *httpReq = mupnp_http_request_new();
  if (!httpReq) {
    round_node_rpcerrorcode2error(node, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR, err);
    return false;
  }
  
  mupnp_http_request_setmethod(httpReq, MUPNP_HTTP_POST);
  mupnp_http_request_seturi(httpReq, ROUND_RPC_HTTP_ENDPOINT);
  mupnp_http_request_setcontentlength(httpReq, 0);
  
  mUpnpHttpResponse *httpRes = mupnp_http_request_post(httpReq, remoteAddr, remotePort);
  if (httpRes) {
    round_node_rpcerrorcode2error(node, ROUND_RPC_ERROR_CODE_BAD_DESTINATION, err);
    mupnp_http_request_delete(httpReq);
    return false;
  }
  
  const char *resContent = mupnp_http_response_getcontent(httpRes);
  if (mupnp_http_response_issuccessful(httpRes)) {
    round_remote_node_sethttpresponse(node, resContent, resMap, err);
  }
  else {
    round_remote_node_sethttpresponse(node, resContent, resMap, err);
  }

  mupnp_http_request_delete(httpReq);
  
  return true;
}
