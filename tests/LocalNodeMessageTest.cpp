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

BOOST_AUTO_TEST_CASE(LocalNodeMessageNew)
{
  RoundMessage *msg = round_local_node_message_new();
  BOOST_CHECK(msg);
  
  BOOST_CHECK(round_local_node_message_delete(msg));
}
