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

#include <round/util/consistent_hashing.h>

#define ROUND_TEST_LIST_SIZE 10

BOOST_AUTO_TEST_CASE(ConsistentHashingRingNew)
{
  RoundConsistentHashingRing *ring = round_consistenthashing_ring_new();
  BOOST_CHECK(ring);
  
  BOOST_CHECK(round_consistenthashing_ring_delete(ring));
}
