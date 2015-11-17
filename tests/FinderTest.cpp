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

#include <round/finder.h>

BOOST_AUTO_TEST_SUITE(finder)

BOOST_AUTO_TEST_CASE(FinderNew)
{
  RoundFinder *finder = round_finder_new();
  BOOST_CHECK(finder);
  
  BOOST_CHECK(round_finder_start(finder));
  BOOST_CHECK(round_finder_search(finder));
  BOOST_CHECK(round_finder_stop(finder));
  
  BOOST_CHECK(round_finder_delete(finder));
}

BOOST_AUTO_TEST_SUITE_END()
