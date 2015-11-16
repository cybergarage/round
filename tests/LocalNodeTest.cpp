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

#include <round/node_internal.h>
#include <round/method/system_method.h>

BOOST_AUTO_TEST_CASE(LocalNodeNew)
{
  RoundLocalNode *node = round_local_node_new();
  BOOST_CHECK(node);
  BOOST_CHECK(round_local_node_delete(node));
}

BOOST_AUTO_TEST_CASE(LocalNodeVirtualNew)
{
  RoundNode *node = (RoundNode *)round_local_node_new();
  BOOST_CHECK(node);
  BOOST_CHECK(round_node_delete(node));
}

BOOST_AUTO_TEST_CASE(LocalSystemMethod)
{
  RoundLocalNode *node = round_local_node_new();
  BOOST_CHECK(node);
  
  BOOST_CHECK(round_local_node_isfinalmethod(node, ROUNDC_SYSTEM_METHOD_SET_METHOD));
  BOOST_CHECK(round_local_node_isfinalmethod(node, ROUNDC_SYSTEM_METHOD_REMOVE_METHOD));
  
  BOOST_CHECK(round_local_node_isfinalmethod(node, ROUNDC_SYSTEM_METHOD_SET_METHOD));
  
  BOOST_CHECK(!round_local_node_setmethod(node, round_system_method_setmethod_new()));

  BOOST_CHECK(!round_local_node_removemethod(node, ROUNDC_SYSTEM_METHOD_SET_METHOD));
  BOOST_CHECK(!round_local_node_removemethod(node, ROUNDC_SYSTEM_METHOD_REMOVE_METHOD));

  BOOST_CHECK(round_local_node_delete(node));
}
