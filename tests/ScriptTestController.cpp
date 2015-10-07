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
#include <boost/lexical_cast.hpp>

#include <sstream>
#include <string.h>

#include <round/round.h>
#include <round/script.h>

#include "ScriptTestController.h"

using namespace std;
using namespace Round;

void Round::Test::ScriptTestController::runEchoMethodTest(RoundMethodManager *scriptMgr) {
  std::vector<std::string> params;
  
  // FIXME Script Error only of SpiderMonkey #23
  // params.push_back("");
  
  params.push_back("1");
  params.push_back("\"1\"");
  params.push_back("\"Hello\"");
  
  params.push_back("[]");
  
  params.push_back("[0]");
  params.push_back("[0,1]");
  params.push_back("[0,1,2]");
  
  params.push_back("[\"0\"]");
  params.push_back("[\"0\",\"1\"]");
  params.push_back("[\"0\",\"1\",\"2\"]");
  
  params.push_back("{}");
  
  params.push_back("{\"key\":0}");
  params.push_back("{\"key0\":0,\"key1\":1}");
  params.push_back("{\"key0\":0,\"key1\":1,\"key2\":2}");
  
  params.push_back("{\"key0\":\"value0\"}");
  params.push_back("{\"key0\":\"value0\",\"key1\":\"value1\"}");
  params.push_back("{\"key0\":\"value0\",\"key1\":\"value1\",\"key2\":\"value2\"}");
  
  /*
  std::string results;
  Error error;
  for (std::vector<std::string>::iterator echoParamIt = params.begin(); echoParamIt != params.end(); echoParamIt++) {
    std::string &echoParam = *echoParamIt;
    BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_ECHO_NAME, echoParam, &results, &error));
    BOOST_CHECK_EQUAL(echoParam.compare(results), 0);
  }
   */
}

void Round::Test::ScriptTestController::runSumMethodTest(RoundMethodManager *scriptMgr) {
  std::vector<std::string> params;
  std::vector<std::string> results;
  
  params.push_back("[1]");
  results.push_back("1");
  
  params.push_back("[1,2]");
  results.push_back("3");
  
  params.push_back("[1,2,3]");
  results.push_back("6");
  
  params.push_back("[0,1,2,3,4,5,6,7,8,9]");
  results.push_back("45");
  
  params.push_back("[10,20,30]");
  results.push_back("60");
  
  params.push_back("[10,20]");
  results.push_back("30");
  
  params.push_back("[10,20,30]");
  results.push_back("60");
  
  params.push_back("[0,10,20,30,40,50,60,70,80,90]");
  results.push_back("450");
  
  size_t nParams = params.size();
  for (size_t n = 0; n < nParams; n++) {
/*
    std::string result;
    Error error;
    BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_SUM_NAME, params[n], &result, &error));
    BOOST_CHECK_EQUAL(result.compare(results[n]), 0);
*/
  }
}

void Round::Test::ScriptTestController::runCounterMethodTest(RoundMethodManager *scriptMgr) {
  std::string result;
/*
  Error error;
  
  const size_t TEST_LOOP_COUNT = 10;

  // set_counter, get_counter
  for (size_t n=0; n<=TEST_LOOP_COUNT; n++) {
    BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_SETCOUNTER_NAME, boost::lexical_cast<std::string>(n), &result, &error));
    BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_GETCOUNTER_NAME, "", &result, &error));
    BOOST_CHECK_EQUAL(boost::lexical_cast<int>(result), n);
  }

  // set_counter, inc_counter, get_counter
  for (size_t n=0; n<=TEST_LOOP_COUNT; n++) {
    BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_INCCOUNTER_NAME, "", &result, &error));
    BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_GETCOUNTER_NAME, "", &result, &error));
    BOOST_CHECK_EQUAL(boost::lexical_cast<int>(result), (n + TEST_LOOP_COUNT + 1));
  }
*/
}

