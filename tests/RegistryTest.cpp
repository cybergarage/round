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

BOOST_AUTO_TEST_CASE(RegistryMember) {
  RoundRegistry *reg = round_registry_new();
  BOOST_CHECK(reg);

  char key[32], val[32];
  clock_t ts, lts;

  snprintf(key, sizeof(key), "key%ld", time(NULL));
  BOOST_CHECK(round_registry_setkey(reg, key));
  BOOST_CHECK_EQUAL(round_registry_getkey(reg), key);

  snprintf(val, sizeof(val), "val%ld", time(NULL));
  BOOST_CHECK(round_registry_setvalue(reg, val));
  BOOST_CHECK_EQUAL(round_registry_getvalue(reg), val);

  ts = time(NULL) + 100;
  round_registry_setts(reg, ts);
  BOOST_CHECK_EQUAL(round_registry_getts(reg), ts);

  lts = time(NULL) - 100;
  round_registry_setlts(reg, lts);
  BOOST_CHECK_EQUAL(round_registry_getlts(reg), lts);

  BOOST_CHECK_EQUAL(round_registry_getkey(reg), key);
  BOOST_CHECK_EQUAL(round_registry_getvalue(reg), val);
  BOOST_CHECK_EQUAL(round_registry_getts(reg), ts);
  BOOST_CHECK_EQUAL(round_registry_getlts(reg), lts);

  BOOST_CHECK(round_registry_delete(reg));
}

BOOST_AUTO_TEST_CASE(RegistryManager) {
  RoundRegistryManager *mgr = round_registry_manager_new();

  BOOST_CHECK(mgr);
  BOOST_CHECK_EQUAL(0, round_registry_manager_size(mgr));

  RoundRegistry *reg[ROUND_TEST_MAP_SIZE];
  char key[32];
  char val[32];

  // Add regs

  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    reg[n] = round_registry_new();
    BOOST_CHECK(reg[n]);
    BOOST_CHECK(!round_registry_manager_set(mgr, reg[n]));

    snprintf(key, sizeof(key), "key%d", n);
    round_registry_setkey(reg[n], key);

    snprintf(val, sizeof(key), "val%d", n);
    round_registry_setvalue(reg[n], key);

    BOOST_CHECK(round_registry_manager_set(mgr, reg[n]));
    BOOST_CHECK_EQUAL((n + 1), round_registry_manager_size(mgr));
  }

  BOOST_CHECK_EQUAL(ROUND_TEST_MAP_SIZE, round_registry_manager_size(mgr));

  // Get regs

  for (int n = 0; n < ROUND_TEST_MAP_SIZE; n++) {
    snprintf(key, sizeof(key), "key%d", n);
    BOOST_CHECK_EQUAL(reg[n], round_registry_manager_get(mgr, key));
    BOOST_CHECK_EQUAL(
    round_registry_getvalue(reg[n]),
    round_registry_getvalue(round_registry_manager_get(mgr, key)));
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
