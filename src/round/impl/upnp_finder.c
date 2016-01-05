/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/finder_internal.h>
#include <round/node_internal.h>

/****************************************
 * round_finder_upnpdevicelistener
 ****************************************/

#if !defined(mupnp_device_getaddress)
#define mupnp_device_getaddress(dev) mupnp_ssdp_packet_getlocaladdress(mupnp_device_getssdppacket(dev))
#endif

void round_finder_upnpdevicelistener(mUpnpControlPoint* cp, const char* udn, mUpnpDeviceStatus devStatus)
{
  RoundFinder* finder = mupnp_controlpoint_getuserdata(cp);
  if (!finder)
    return;

  mUpnpDevice* dev = mupnp_controlpoint_getdevicebyudn(cp, (char*)udn);
  if (!dev)
    return;

  if (!mupnp_device_isdevicetype(dev, ROUND_UPNP_DEVICE_TYPE))
    return;

  RoundNode* node = round_node_new();
  round_node_setaddress(node, mupnp_device_getaddress(dev));
  round_node_setport(node, mupnp_device_gethttpport(dev));

  switch (devStatus) {
  case mUpnpDeviceStatusAdded:
  case mUpnpDeviceStatusUpdated: {
    if (finder->addedListener) {
      finder->addedListener(finder, node);
    }
  } break;
  case mUpnpDeviceStatusRemoved: {
    if (finder->removedListener) {
      finder->removedListener(finder, node);
    }
  } break;
  default:
    break;
  }

  round_node_delete(node);
}

/****************************************
 * round_finder_new
 ****************************************/

RoundFinder* round_finder_new(void)
{
  RoundFinder* finder;

  finder = (RoundFinder*)malloc(sizeof(RoundFinder));

  if (!finder)
    return NULL;

  finder->cp = mupnp_controlpoint_new();

  if (!finder->cp) {
    round_finder_delete(finder);
    return NULL;
  }

  round_finder_setuserdata(finder, NULL);
  round_finder_setnodeaddedlistener(finder, NULL);
  round_finder_setnoderemovedlistener(finder, NULL);

  mupnp_controlpoint_setuserdata(finder->cp, finder);
  mupnp_controlpoint_setdevicelistener(finder->cp, round_finder_upnpdevicelistener);

  return finder;
}

/****************************************
 * round_finder_delete
 ****************************************/

bool round_finder_delete(RoundFinder* finder)
{
  if (!finder)
    return false;

  if (finder->cp) {
    mupnp_controlpoint_delete(finder->cp);
  }

  free(finder);

  return true;
}

/****************************************
 * round_finder_start
 ****************************************/

bool round_finder_start(RoundFinder* finder)
{
  if (!finder)
    return false;

  return mupnp_controlpoint_start(finder->cp);
}

/****************************************
 * round_finder_stop
 ****************************************/

bool round_finder_stop(RoundFinder* finder)
{
  if (!finder)
    return false;

  return mupnp_controlpoint_stop(finder->cp);
}

/****************************************
 * round_finder_search
 ****************************************/

bool round_finder_search(RoundFinder* finder)
{
  if (!finder)
    return false;

  return mupnp_controlpoint_search(finder->cp, ROUND_UPNP_DEVICE_TYPE);
}
