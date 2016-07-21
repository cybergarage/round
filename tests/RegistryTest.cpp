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
#include <round/registry.h>

#define ROUND_TEST_REGISTRY_LOOP_CNT 10

BOOST_AUTO_TEST_SUITE(registry)

BOOST_AUTO_TEST_CASE(RegistryBasicMembers)
{
  RoundRegistry* reg = round_registry_new();
  BOOST_CHECK(reg);

  char key[32], val[32];
  const char *rval;
  clock_t ts, lts;

  snprintf(key, sizeof(key), "key%ld", time(NULL));
  BOOST_CHECK(round_registry_setkey(reg, key));
  BOOST_CHECK_EQUAL(round_registry_getkey(reg), key);

  snprintf(val, sizeof(val), "val%ld", time(NULL));
  BOOST_CHECK(round_registry_setstring(reg, val));
  BOOST_CHECK(round_registry_getstring(reg, &rval));
  BOOST_CHECK(round_streq(val, rval));

  ts = time(NULL) + 100;
  round_registry_setts(reg, ts);
  BOOST_CHECK_EQUAL(round_registry_getts(reg), ts);

  lts = time(NULL) - 100;
  round_registry_setlts(reg, lts);
  BOOST_CHECK_EQUAL(round_registry_getlts(reg), lts);

  BOOST_CHECK_EQUAL(round_registry_getkey(reg), key);
  BOOST_CHECK(round_registry_getstring(reg, &rval));
  BOOST_CHECK(round_streq(val, rval));
  BOOST_CHECK_EQUAL(round_registry_getts(reg), ts);
  BOOST_CHECK_EQUAL(round_registry_getlts(reg), lts);

  BOOST_CHECK(round_registry_delete(reg));
}

BOOST_AUTO_TEST_CASE(RegistryTypes)
{
  RoundRegistry* reg = round_registry_new();
  BOOST_CHECK(reg);
  BOOST_CHECK(round_registry_isunknown(reg));
  
  // Set string values
  
  for (int n=0; n<ROUND_TEST_REGISTRY_LOOP_CNT; n++) {
    char val[32];
    const char *rval;
    snprintf(val, sizeof(val), "value%d", n);
    BOOST_CHECK(round_registry_setstring(reg, val));
    BOOST_CHECK(round_registry_isstring(reg));
    BOOST_CHECK(round_registry_getstring(reg, &rval));
    BOOST_CHECK(round_streq(val, rval));
  }
  BOOST_CHECK(round_registry_clear(reg));
  BOOST_CHECK(round_registry_isunknown(reg));
  
  // Set integer values
  
  for (int n=0; n<ROUND_TEST_REGISTRY_LOOP_CNT; n++) {
    int rval;
    BOOST_CHECK(round_registry_setinteger(reg, n));
    BOOST_CHECK(round_registry_isinteger(reg));
    BOOST_CHECK(round_registry_getinteger(reg, &rval));
    BOOST_CHECK_EQUAL(n, rval);
  }
  BOOST_CHECK(round_registry_clear(reg));
  BOOST_CHECK(round_registry_isunknown(reg));
  
  // Set real values
  
  for (int n=0; n<ROUND_TEST_REGISTRY_LOOP_CNT; n++) {
    double rval;
    BOOST_CHECK(round_registry_setreal(reg, n));
    BOOST_CHECK(round_registry_isreal(reg));
    BOOST_CHECK(round_registry_getreal(reg, &rval));
    BOOST_CHECK_EQUAL(n, (int)rval);
  }
  BOOST_CHECK(round_registry_clear(reg));
  BOOST_CHECK(round_registry_isunknown(reg));
  
  BOOST_CHECK(round_registry_delete(reg));
}

BOOST_AUTO_TEST_CASE(RegistryManager)
{
  RoundRegistryManager* mgr = round_registry_manager_new();

  BOOST_CHECK(mgr);
  BOOST_CHECK_EQUAL(0, round_registry_manager_size(mgr));

  RoundRegistry* reg[ROUND_TEST_MAP_SIZE];
  char key[32];
  char val[32];
  const char *rval, *rregval;
  RoundRegistry *rreg;
  
  // Add regs

  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    reg[n] = round_registry_new();
    BOOST_CHECK(reg[n]);
    BOOST_CHECK(!round_registry_manager_set(mgr, reg[n]));

    snprintf(key, sizeof(key), "key%d", n);
    round_registry_setkey(reg[n], key);

    snprintf(val, sizeof(key), "val%d", n);
    round_registry_setstring(reg[n], key);

    BOOST_CHECK(round_registry_manager_set(mgr, reg[n]));
    BOOST_CHECK_EQUAL((n + 1), round_registry_manager_size(mgr));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_registry_manager_size(mgr));

  // Get regs

  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    snprintf(key, sizeof(key), "key%d", n);
    BOOST_CHECK_EQUAL(reg[n], round_registry_manager_get(mgr, key));
    BOOST_CHECK(round_registry_getstring(reg[n], &rval));
    rreg = round_registry_manager_get(mgr, key);
    BOOST_CHECK(rreg);
    BOOST_CHECK(round_registry_getstring(rreg, &rregval));
    BOOST_CHECK(round_streq(rval, rregval));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_registry_manager_size(mgr));

  // Remove regs

  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    snprintf(key, sizeof(key), "key%d", n);
    BOOST_CHECK(round_registry_manager_remove(mgr, key));
    BOOST_CHECK(!round_registry_manager_get(mgr, key));
    BOOST_CHECK_EQUAL((ROUND_TEST_MAP_SIZE - (n + 1)),
        round_registry_manager_size(mgr));
  }

  BOOST_CHECK_EQUAL(0, round_registry_manager_size(mgr));

  BOOST_CHECK(round_registry_manager_delete(mgr));
}

BOOST_AUTO_TEST_SUITE_END()
