/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include "RoundTest.h"
#include <round/route.h>

BOOST_AUTO_TEST_SUITE(route)

BOOST_AUTO_TEST_CASE(RouteObjectNew)
{
  RoundRouteObject* obj = round_route_object_new();
  BOOST_CHECK(obj);
  
  BOOST_CHECK_EQUAL(round_route_object_hasname(obj), false);
  BOOST_CHECK_EQUAL(round_route_object_hastarget(obj), false);
  BOOST_CHECK_EQUAL(round_route_object_gettype(obj), RoundRouteObjectNone);
  BOOST_CHECK_EQUAL(round_route_object_gettarget(obj), (RoundRouteTarget *)NULL);
  
  BOOST_CHECK(round_route_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(RouteNew)
{
  RoundRoute* route = round_route_new();
  BOOST_CHECK(route);
  
  BOOST_CHECK_EQUAL(round_route_hasname(route), false);
  BOOST_CHECK_EQUAL(round_route_hassourceobject(route), true);
  BOOST_CHECK_EQUAL(round_route_hasdestinationobject(route), true);
  
  BOOST_CHECK(round_route_delete(route));
}

BOOST_AUTO_TEST_SUITE_END()