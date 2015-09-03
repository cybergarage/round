/******************************************************************
 *
 * Round SDK for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/finder.h>

/****************************************
 * round_finder_new
 ****************************************/

RoundFinder *round_finder_new(void)
{
  RoundFinder *finder;
  
  finder = (RoundFinder *)malloc(sizeof(RoundFinder));
  
  if (!finder)
    return NULL;
  
  finder->cp = mupnp_controlpoint_new();
  
  return finder;
}

/****************************************
 * round_finder_delete
 ****************************************/

bool round_finder_delete(RoundFinder *finder)
{
  if (!finder)
    return false;
  
  mupnp_controlpoint_delete(finder->cp);
  
  free(finder);
  
  return true;
}

/****************************************
 * round_finder_start
 ****************************************/

bool round_finder_start(RoundFinder *finder)
{
  if (!finder)
    return false;

  return mupnp_controlpoint_start(finder->cp);
}

/****************************************
 * round_finder_stop
 ****************************************/

bool round_finder_stop(RoundFinder *finder)
{
  if (!finder)
    return false;
  
  return mupnp_controlpoint_stop(finder->cp);
}

/****************************************
 * round_finder_search
 ****************************************/

bool round_finder_search(RoundFinder *finder)
{
  if (!finder)
    return false;
  
  return mupnp_controlpoint_search(finder->cp, ROUNDC_UPNP_DEVICE_TYPE);
}

