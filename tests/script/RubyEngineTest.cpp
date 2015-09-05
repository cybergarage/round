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
#include <string>

#include <round/script/ruby.h>

#if defined(ROUND_SUPPORT_RUBY) ||  defined(ROUND_SUPPORT_MRUBY)

BOOST_AUTO_TEST_CASE(RubyEngineTest) {
  RoundRubyEngine *rubyEngine;
  
  rubyEngine = round_ruby_engine_new();
  
  BOOST_CHECK(round_ruby_engine_delete(rubyEngine));
}

#endif
