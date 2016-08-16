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

#include <round/trigger.h>

BOOST_AUTO_TEST_SUITE(trigger)

BOOST_AUTO_TEST_CASE(TriggerNew)
{
  RoundTrigger *trigger = round_trigger_new();
  
  round_trigger_delete(trigger);
}

BOOST_AUTO_TEST_SUITE_END()
