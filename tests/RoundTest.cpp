/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#define BOOST_TEST_MODULE RoundSdkTest
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/random.hpp>
#include <boost/thread.hpp>

#include "RoundTest.h"

struct RoundFixture {
  RoundFixture()
  {
    Round::Test::Setup();
  }

  ~RoundFixture()
  {
  }
};

BOOST_GLOBAL_FIXTURE(RoundFixture);

void Round::Test::Setup()
{
}

int Round::Test::GetRandomRepeatCount(int min, int max)
{
#if defined(ROUND_HAVE_BOOST_RANDOM)
  boost::random::mt19937 rndEngine;
  boost::random::uniform_int_distribution<> randDist(min, max);
#else
  boost::mt19937 rndEngine;
  boost::uniform_smallint<> randDist(min, max);
#endif
  return randDist(rndEngine);
}

void Round::Test::Sleep(long milliSecond)
{
  boost::this_thread::sleep(boost::posix_time::milliseconds(milliSecond));
}
