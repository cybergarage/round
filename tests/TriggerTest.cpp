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
  
  BOOST_CHECK_EQUAL(round_trigger_hasname(trigger), false);
  
  BOOST_CHECK_EQUAL(round_trigger_isloop(trigger), false);
  BOOST_CHECK_EQUAL(round_trigger_getcycleinterval(trigger), 0.0);
  
  BOOST_CHECK_EQUAL(round_trigger_getstarttime(trigger), 0.0);
  BOOST_CHECK_EQUAL(round_trigger_isstarttimeenabled(trigger), false);
  
  BOOST_CHECK_EQUAL(round_trigger_getstoptime(trigger), 0.0);
  BOOST_CHECK_EQUAL(round_trigger_isstoptimeenabled(trigger), false);
  
  round_trigger_delete(trigger);
}

BOOST_AUTO_TEST_CASE(TriggerMembers)
{
  static const char *TRIGGER_TEST_NAME = "testtrigger";
  
  RoundTrigger *trigger = round_trigger_new();
  
  BOOST_CHECK_EQUAL(round_trigger_hasname(trigger), false);
  BOOST_CHECK_EQUAL(round_trigger_setname(trigger, TRIGGER_TEST_NAME), true);
  BOOST_CHECK_EQUAL(round_trigger_hasname(trigger), true);
  BOOST_CHECK_EQUAL(round_trigger_isname(trigger, TRIGGER_TEST_NAME), true);
  
  round_trigger_delete(trigger);
}

BOOST_AUTO_TEST_CASE(TriggerManagerNew)
{
  RoundTriggerManager *triggerMgr = round_trigger_manager_new();
  
  round_trigger_manager_delete(triggerMgr);
}

BOOST_AUTO_TEST_SUITE_END()
