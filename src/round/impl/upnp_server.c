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
* round_upnp_server_httprequestrecieved
****************************************/

void round_upnp_server_httprequestrecieved(mUpnpHttpRequest *httpReq)
{
	mUpnpDevice *dev = (mUpnpDevice *)mupnp_http_request_getuserdata(httpReq);

	char *uri = mupnp_http_request_geturi(httpReq);
	if (strcmp(uri, ROUNDC_RPC_HTTP_ENDPOINT) != 0) {
		mupnp_device_httprequestrecieved(httpReq);
		return;
	}

  char *content = "";
  
	mUpnpHttpResponse *httpRes = mupnp_http_response_new();
	mupnp_http_response_setstatuscode(httpRes, MUPNP_HTTP_STATUS_OK);
	mupnp_http_response_setcontent(httpRes, content);
	mupnp_http_response_setcontenttype(httpRes, "text/html");
	mupnp_http_response_setcontentlength(httpRes, strlen(content));
	mupnp_http_request_postresponse(httpReq, httpRes);
  mupnp_http_response_delete(httpRes);
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
