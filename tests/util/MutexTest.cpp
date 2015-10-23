/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>
#include <round/round.h>

BOOST_AUTO_TEST_SUITE(mutex)

BOOST_AUTO_TEST_CASE(MutexTest)
{
  RoundMutex *mutex;
  
  mutex = round_mutex_new();
  BOOST_CHECK(mutex);
  BOOST_CHECK(round_mutex_lock(mutex));
  BOOST_CHECK(round_mutex_unlock(mutex));
  BOOST_CHECK(round_mutex_delete(mutex));
}

BOOST_AUTO_TEST_SUITE_END()
