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
#include <round/util/strings.h>
#include <round/util/json.h>
#include <round/impl/upnp_server.h>
#include <round/impl/upnp_server_desc.h>

/****************************************
 * round_upnp_server_actionreceived
 ****************************************/

bool round_upnp_server_actionreceived(mUpnpAction *action)
{
  return false;
}

/****************************************
 * round_upnp_server_queryreceived
 ****************************************/

bool round_upnp_server_queryreceived(mUpnpStateVariable *statVar)
{
  return false;
}

/****************************************
 * round_upnp_server_isjsonrpcrequest
 ****************************************/

bool round_upnp_server_isjsonrpcrequest(mUpnpHttpRequest *httpReq)
{
  if (!mupnp_http_request_ispostrequest(httpReq))
    return false;
  
  char *uri = mupnp_http_request_geturi(httpReq);
  if (!round_streq(uri, ROUNDC_RPC_HTTP_ENDPOINT))
    return false;
  
  // TODO : Check content type

  return true;
}

/****************************************
 * round_upnp_server_jsonrpcrequestrecieved
 ****************************************/

void round_upnp_server_posterrorresponse(mUpnpHttpRequest *httpReq, int rpcErrCode)
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
 * round_upnp_server_hasjsonrpcparameters
 ****************************************/

bool round_upnp_server_hasjsonrpcparameters(mUpnpHttpRequest *httpReq)
{
  return true;
}

/****************************************
 * round_upnp_server_jsonrpcrequestrecieved
 ****************************************/

void round_upnp_server_jsonrpcrequestrecieved(mUpnpHttpRequest *httpReq)
{
  const char *jsonContent = mupnp_http_request_getcontent(httpReq);
  if (jsonContent) {
    round_upnp_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_INVALID_REQUEST);
    return;
  }
  
  RoundJSON *json = round_json_new();
  if (!json) {
    round_upnp_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_INTERNAL_ERROR);
    return;
  }
  
  if (round_json_parse(json, jsonContent, NULL)) {
    round_json_delete(json);
    round_upnp_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_PARSER_ERROR);
    return;
  }

  if (!round_upnp_server_hasjsonrpcparameters(httpReq))) {
    round_json_delete(json);
    round_upnp_server_posterrorresponse(httpReq, ROUNDC_RPC_ERROR_CODE_PARSER_ERROR);
    return;
  }
  
  round_json_delete(json);
}

/****************************************
* round_upnp_server_httprequestrecieved
****************************************/

void round_upnp_server_httprequestrecieved(mUpnpHttpRequest *httpReq)
{
  if (round_upnp_server_isjsonrpcrequest(httpReq)) {
    round_upnp_server_jsonrpcrequestrecieved(httpReq);
    return;
  }

  mupnp_device_httprequestrecieved(httpReq);
}

/****************************************
* round_upnp_server_new
****************************************/

mUpnpDevice *round_upnp_server_new(void)
{
  mUpnpDevice *upnpDev = mupnp_device_new();
  if (!upnpDev)
    return NULL;

  if (mupnp_device_parsedescription(upnpDev, ROUNDC_UPNP_SERVER_DEVICE_DESCRIPTION, strlen(ROUNDC_UPNP_SERVER_DEVICE_DESCRIPTION)) == false) {
    mupnp_device_delete(upnpDev);
    return NULL;
  }
  
  mUpnpService *upnpSrv = mupnp_device_getservicebyexacttype(upnpDev, ROUNDC_UPNP_SERVICE_TYPE);
  if (upnpSrv == NULL) {
    mupnp_device_delete(upnpDev);
    return NULL;
  }
  
  if (mupnp_service_parsedescription(upnpSrv, ROUNDC_UPNP_SERVER_SERVICE_DESCRIPTION, strlen(ROUNDC_UPNP_SERVER_SERVICE_DESCRIPTION)) == false) {
    mupnp_device_delete(upnpDev);
    return NULL;
  }
  
  mupnp_device_setactionlistener(upnpDev, round_upnp_server_actionreceived);
  mupnp_device_setquerylistener(upnpDev, round_upnp_server_queryreceived);
  mupnp_device_sethttplistener(upnpDev, round_upnp_server_httprequestrecieved);
  
  return upnpDev;
}
