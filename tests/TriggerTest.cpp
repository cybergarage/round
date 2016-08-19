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
  static const int TEST_TRIGGER_NUM = 10;
  
  RoundTriggerManager *mgr = round_trigger_manager_new();
  BOOST_CHECK(mgr);
  
  BOOST_CHECK_EQUAL(round_trigger_manager_size(mgr), 0);
  
  RoundTrigger* trigger;
  char name[64];
  
  // Add triggers
  
  for (size_t n = 0; n < TEST_TRIGGER_NUM; n++) {
    snprintf(name, sizeof(name), "%ld", n);
    trigger = round_trigger_new();
    round_trigger_setname(trigger, name);
    BOOST_CHECK(round_trigger_manager_settrigger(mgr, trigger));
    BOOST_CHECK(round_trigger_manager_hastriggerbyname(mgr, name));
    BOOST_CHECK_EQUAL(round_trigger_manager_size(mgr), (n + 1));
  }
  
  BOOST_CHECK_EQUAL(round_trigger_manager_size(mgr), TEST_TRIGGER_NUM);
  
  // Get triggers by name
  
  for (size_t n = 0; n < TEST_TRIGGER_NUM; n++) {
    snprintf(name, sizeof(name), "%ld", n);
    trigger = round_trigger_manager_gettriggerbyname(mgr, name);
    BOOST_CHECK(trigger);
  }
  
  BOOST_CHECK_EQUAL(round_trigger_manager_size(mgr), TEST_TRIGGER_NUM);
  
  // Add same triggers
  
  for (size_t n = 0; n < TEST_TRIGGER_NUM; n++) {
    snprintf(name, sizeof(name), "%ld", n);
    trigger = round_trigger_new();
    round_trigger_setname(trigger, name);
    BOOST_CHECK(round_trigger_manager_settrigger(mgr, trigger));
    BOOST_CHECK_EQUAL(round_trigger_manager_size(mgr), TEST_TRIGGER_NUM);
  }
  
  BOOST_CHECK_EQUAL(round_trigger_manager_size(mgr), TEST_TRIGGER_NUM);
  
  // Remove triggers by name
  
  for (size_t n = 0; n < TEST_TRIGGER_NUM; n++) {
    snprintf(name, sizeof(name), "%ld", n);
    BOOST_CHECK(round_trigger_manager_removetriggerbyname(mgr, name));
    BOOST_CHECK_EQUAL(round_trigger_manager_hastriggerbyname(mgr, name), false);
    BOOST_CHECK_EQUAL(round_trigger_manager_size(mgr), (TEST_TRIGGER_NUM - (n + 1)));
  }
  
  BOOST_CHECK_EQUAL(round_trigger_manager_size(mgr), 0);
  
  BOOST_CHECK(round_trigger_manager_delete(mgr));
}

BOOST_AUTO_TEST_SUITE_END()
