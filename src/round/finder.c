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
