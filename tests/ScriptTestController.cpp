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
#include <boost/lexical_cast.hpp>

#include <sstream>
#include <string.h>

#include <round/script.h>
#include <round/util/strings.h>

#include "ScriptTestController.h"

using namespace std;
using namespace Round;

RoundMethod* Round::Test::CreateTestMethod(const char* name, const char* lang, const char* stringCode)
{
  RoundMethod* method = round_method_new();
  if (!method)
    return NULL;

  round_method_setname(method, name);
  round_method_setlanguage(method, lang);
  round_method_setstringcode(method, stringCode);

  return method;
}

void Round::Test::ScriptTestController::runEchoMethodTest(RoundMethodManager* scriptMgr)
{
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

  RoundJSONObject* resultObj;
  RoundError* err = round_error_new();

  for (std::vector<std::string>::iterator echoParamIt = params.begin(); echoParamIt != params.end(); echoParamIt++) {
    std::string& echoParam = *echoParamIt;
    bool isSuccess;
    BOOST_CHECK(isSuccess = round_method_manager_execmethod(scriptMgr, Round::Test::SCRIPT_ECHO_NAME, echoParam.c_str(), &resultObj, err));
    if (!isSuccess)
      continue;

    BOOST_CHECK(resultObj);
    if (!resultObj)
      continue;

    const char* resultStr = NULL;
    BOOST_CHECK(round_json_object_tostringwithoption(resultObj, (RoundJSONOptionFormatCompact | RoundJSONOptionFormatSort), &resultStr));
    BOOST_CHECK(resultStr);

    if (resultStr) {
      char* compackResultStr = round_strreplace(resultStr, " ", "");
      BOOST_CHECK_EQUAL(echoParam.c_str(), compackResultStr);
      free(compackResultStr);
    }

    round_json_object_delete(resultObj);
  }

  round_error_delete(err);
}

void Round::Test::ScriptTestController::runSumMethodTest(RoundMethodManager* scriptMgr)
{
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

  RoundJSONObject* resultObj;
  RoundError* err = round_error_new();

  size_t nParams = params.size();
  for (size_t n = 0; n < nParams; n++) {
    bool isSuccess;
    BOOST_CHECK(isSuccess = round_method_manager_execmethod(
                    scriptMgr, Round::Test::SCRIPT_SUM_NAME, params[n].c_str(), &resultObj, err));
    if (!isSuccess)
      continue;

    BOOST_CHECK(resultObj);
    if (!resultObj)
      continue;

    const char* resultStr = NULL;
    BOOST_CHECK(round_json_object_tostringwithoption(
        resultObj, (RoundJSONOptionFormatCompact | RoundJSONOptionFormatSort), &resultStr));
    BOOST_CHECK(resultStr);
    BOOST_CHECK_EQUAL(results[n].c_str(), resultStr);

    round_json_object_delete(resultObj);
  }
}

void Round::Test::ScriptTestController::runCounterMethodTest(RoundMethodManager* scriptMgr)
{
  std::string result;
  /*
    Error error;

    const size_t TEST_LOOP_COUNT = 10;

    // set_counter, get_counter
    for (size_t n=0; n<=TEST_LOOP_COUNT; n++) {
      BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_SETCOUNTER_NAME,
    boost::lexical_cast<std::string>(n), &result, &error));
      BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_GETCOUNTER_NAME, "",
    &result, &error));
      BOOST_CHECK_EQUAL(boost::lexical_cast<int>(result), n);
    }

    // set_counter, inc_counter, get_counter
    for (size_t n=0; n<=TEST_LOOP_COUNT; n++) {
      BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_INCCOUNTER_NAME, "",
    &result, &error));
      BOOST_CHECK(scriptMgr->execMethod(Test::SCRIPT_GETCOUNTER_NAME, "",
    &result, &error));
      BOOST_CHECK_EQUAL(boost::lexical_cast<int>(result), (n + TEST_LOOP_COUNT +
    1));
    }
  */
}
