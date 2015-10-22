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

#include <round/util/strings.h>

BOOST_AUTO_TEST_SUITE(string)

BOOST_AUTO_TEST_CASE(IsNumeric)
{
  BOOST_CHECK_EQUAL(round_isnumeric(NULL), false);
  BOOST_CHECK_EQUAL(round_isnumeric(""), false);
  BOOST_CHECK_EQUAL(round_isnumeric("a"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("abc"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("#"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("#$%"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("1234567890a"), false);
  BOOST_CHECK_EQUAL(round_isnumeric("1234567890#"), false);

  BOOST_CHECK_EQUAL(round_isnumeric("0"), true);
  BOOST_CHECK_EQUAL(round_isnumeric("1"), true);
  BOOST_CHECK_EQUAL(round_isnumeric("12"), true);
  BOOST_CHECK_EQUAL(round_isnumeric("1234567890"), true);
}

BOOST_AUTO_TEST_CASE(StringReplace)
{
  std::vector<std::string> strings;
  std::vector<std::string> froms;
  std::vector<std::string> tos;
  std::vector<std::string> expects;

  // str == ""
  
  strings.push_back("");
  froms.push_back("");
  tos.push_back("");
  expects.push_back("");
  
  // from == ""
  
  strings.push_back("123456789");
  froms.push_back("");
  tos.push_back("");
  expects.push_back("123456789");
  
  // from == to
   
  strings.push_back("123456789");
  froms.push_back("5");
  tos.push_back("a");
  expects.push_back("1234a6789");

  strings.push_back("123456789");
  froms.push_back("456");
  tos.push_back("abc");
  expects.push_back("123abc789");
  strings.push_back("523456785");
  froms.push_back("5");
  tos.push_back("b");
  expects.push_back("b234b678b");
 
  // from < to
   
  strings.push_back("123456789");
  froms.push_back("5");
  tos.push_back("abc");
  expects.push_back("1234abc6789");
  
  strings.push_back("523456785");
  froms.push_back("5");
  tos.push_back("abc");
  expects.push_back("abc234abc678abc");
  
  // from > to
  strings.push_back("123456789");
  froms.push_back("456");
  tos.push_back("a");
  expects.push_back("123a789");
  
  // to == ""
  
  strings.push_back("123456789");
  froms.push_back("5");
  tos.push_back("");
  expects.push_back("12346789");
  
  strings.push_back("123456789");
  froms.push_back("456");
  tos.push_back("");
  expects.push_back("123789");

  // Test
  
  size_t testCnt = strings.size();
  for (size_t n = 0; n < testCnt; n++) {
    char *result = round_strreplace(strings[n].c_str(), froms[n].c_str(), tos[n].c_str());
    BOOST_CHECK_EQUAL(expects[n].compare(result), 0);
  }
}

BOOST_AUTO_TEST_SUITE_END()

