/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_TESTSCRIPT_H_
#define _ROUNDCC_TESTSCRIPT_H_

#include <round/method.h>

#include "RoundTest.h"

namespace Round {
 
namespace Test {

static const char *SCRIPT_ECHO_NAME = "echo";
static const char *SCRIPT_SUM_NAME = "sum";
static const char *SCRIPT_COUNTER_NAME = "Counter"; // Only Java Platform
static const char *SCRIPT_SETCOUNTER_NAME = "set_counter";
static const char *SCRIPT_INCCOUNTER_NAME = "inc_counter";
static const char *SCRIPT_GETCOUNTER_NAME = "get_counter";

////////////////////////////////////////////////////////////
// JavaScript
////////////////////////////////////////////////////////////

static const char *JS_ECHO_CODE = \
  "function echo(params) {"\
  "  return params;"\
  "}";

static const char *JS_SUM_CODE = \
  "function sum(params) {"\
  "  var sum = 0;"\
  "  for (i = 0; i < params.length; i++) {"\
  "    sum += params[i];"\
  "  }"\
  "  return sum;"\
  "}";

static const char *JS_SETCOUNTER_CODE = \
  "var global = new Function(\"return this\")();"\
  "function set_counter(params) {"\
  "  global.counter = params;"\
  "  return global.counter;"\
  "}";
  
static const char *JS_INCREMENTCOUNTER_CODE = \
  "var global = new Function(\"return this\")();"\
  "function inc_counter(params) {"\
  "  global.counter++;"\
  "  return global.counter;"\
  "}";
  
static const char *JS_GETCOUNTER_CODE = \
  "var global = new Function(\"return this\")();"\
  "function get_counter(params) {"\
  "  return global.counter;"\
  "}";
  
////////////////////////////////////////////////////////////
// Java
////////////////////////////////////////////////////////////

static const char *JAVA_ECHO_SOURCE = "round/tests/scripts/echo.java";
static const char *JAVA_ECHO_CODE = "yv66vgAAADIADwoAAwAMBwANBwAOAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEADnByb2Nlc3NNZXNzYWdlAQAmKExqYXZhL2xhbmcvU3RyaW5nOylMamF2YS9sYW5nL1N0cmluZzsBAApTb3VyY2VGaWxlAQAJZWNoby5qYXZhDAAEAAUBAARlY2hvAQAQamF2YS9sYW5nL09iamVjdAAhAAIAAwAAAAAAAgABAAQABQABAAYAAAAhAAEAAQAAAAUqtwABsQAAAAEABwAAAAoAAgAAAAIABAADAAEACAAJAAEABgAAABoAAQACAAAAAiuwAAAAAQAHAAAABgABAAAABQABAAoAAAACAAs=";

static const char *JAVA_SUM_SOURCE = "round/tests/scripts/sum.java";
static const char *JAVA_SUM_CODE = "yv66vgAAADIAKQoACQAXBwAYCAAZCgACABoHABsKABwAHQoAAgAeBwAfBwAgAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEADnByb2Nlc3NNZXNzYWdlAQAmKExqYXZhL2xhbmcvU3RyaW5nOylMamF2YS9sYW5nL1N0cmluZzsBAA1TdGFja01hcFRhYmxlBwAfBwAYBwAhBwAbAQAKU291cmNlRmlsZQEACHN1bS5qYXZhDAAKAAsBABBqYXZhL2xhbmcvU3RyaW5nAQAGW14wLTldDAAiACMBABNqYXZhL2xhbmcvRXhjZXB0aW9uBwAkDAAlACYMACcAKAEAA3N1bQEAEGphdmEvbGFuZy9PYmplY3QBABNbTGphdmEvbGFuZy9TdHJpbmc7AQAFc3BsaXQBACcoTGphdmEvbGFuZy9TdHJpbmc7KVtMamF2YS9sYW5nL1N0cmluZzsBABFqYXZhL2xhbmcvSW50ZWdlcgEACHBhcnNlSW50AQAVKExqYXZhL2xhbmcvU3RyaW5nOylJAQAHdmFsdWVPZgEAFShJKUxqYXZhL2xhbmcvU3RyaW5nOwAhAAgACQAAAAAAAgABAAoACwABAAwAAAAhAAEAAQAAAAUqtwABsQAAAAEADQAAAAoAAgAAAAQABAAFAAEADgAPAAEADAAAAKcAAwAGAAAANgO9AAJNKxIDtgAETacABE4DPgM2BBUELL6iABgdLBUEMrgABmA+pwAFOgWEBAGn/+cduAAHsAACAAUADAAPAAUAHAAmACkABQACAA0AAAAmAAkAAAAHAAUACQAMAAoAEAALABIADAAcAA4AJgAPACsADAAxABEAEAAAACMABv8ADwADBwARBwASBwATAAEHABQA/QAEAQFTBwAUAfoABQABABUAAAACABY=";

static const char *JAVA_COUNTER_SOURCE = "round/tests/scripts/Counter.java";
static const char *JAVA_COUNTER_CODE = "yv66vgAAADIAFwoABAATCQADABQHABUHABYBAAV2YWx1ZQEAAUkBAAY8aW5pdD4BAAMoKVYBAARDb2RlAQAPTGluZU51bWJlclRhYmxlAQAKU2V0Q291bnRlcgEABChJKVYBABBJbmNyZW1lbnRDb3VudGVyAQAKR2V0Q291bnRlcgEAAygpSQEACDxjbGluaXQ+AQAKU291cmNlRmlsZQEADENvdW50ZXIuamF2YQwABwAIDAAFAAYBAAdDb3VudGVyAQAQamF2YS9sYW5nL09iamVjdAAxAAMABAAAAAEACQAFAAYAAAAFAAEABwAIAAEACQAAAB0AAQABAAAABSq3AAGxAAAAAQAKAAAABgABAAAAAQApAAsADAABAAkAAAAhAAEAAQAAAAUaswACsQAAAAEACgAAAAoAAgAAAAYABAAHACkADQAIAAEACQAAACUAAgAAAAAACbIAAgRgswACsQAAAAEACgAAAAoAAgAAAAoACAALACkADgAPAAEACQAAABwAAQAAAAAABLIAAqwAAAABAAoAAAAGAAEAAAAOAAgAEAAIAAEACQAAAB0AAQAAAAAABQOzAAKxAAAAAQAKAAAABgABAAAAAwABABEAAAACABI=";

static const char *JAVA_SETCOUNTER_SOURCE = "round/tests/scripts/set_counter.java";
static const char *JAVA_SETCOUNTER_CODE = "yv66vgAAADIAJQoABwASCgATABQJABUAFgcAFwoAGAAZBwAaBwAbAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEADnByb2Nlc3NNZXNzYWdlAQAmKExqYXZhL2xhbmcvU3RyaW5nOylMamF2YS9sYW5nL1N0cmluZzsBAA1TdGFja01hcFRhYmxlBwAXAQAKU291cmNlRmlsZQEAEHNldF9jb3VudGVyLmphdmEMAAgACQcAHAwAHQAeBwAfDAAgACEBABNqYXZhL2xhbmcvRXhjZXB0aW9uBwAiDAAjACQBAAtzZXRfY291bnRlcgEAEGphdmEvbGFuZy9PYmplY3QBABFqYXZhL2xhbmcvSW50ZWdlcgEACHBhcnNlSW50AQAVKExqYXZhL2xhbmcvU3RyaW5nOylJAQAHQ291bnRlcgEABXZhbHVlAQABSQEAEGphdmEvbGFuZy9TdHJpbmcBAAd2YWx1ZU9mAQAVKEkpTGphdmEvbGFuZy9TdHJpbmc7ACEABgAHAAAAAAACAAEACAAJAAEACgAAACEAAQABAAAABSq3AAGxAAAAAQALAAAACgACAAAABQAEAAYAAQAMAA0AAQAKAAAATQABAAMAAAAUK7gAAj0cswADpwAETbIAA7gABbAAAQAAAAkADAAEAAIACwAAABIABAAAAAoABQALAAkADAANAA4ADgAAAAcAAkwHAA8AAAEAEAAAAAIAEQ==";

static const char *JAVA_GETCOUNTER_SOURCE = "round/tests/scripts/get_counter.java";
static const char *JAVA_GETCOUNTER_CODE = "yv66vgAAADIAGwoABQAOCQAPABAKABEAEgcAEwcAFAEABjxpbml0PgEAAygpVgEABENvZGUBAA9MaW5lTnVtYmVyVGFibGUBAA5wcm9jZXNzTWVzc2FnZQEAJihMamF2YS9sYW5nL1N0cmluZzspTGphdmEvbGFuZy9TdHJpbmc7AQAKU291cmNlRmlsZQEAEGdldF9jb3VudGVyLmphdmEMAAYABwcAFQwAFgAXBwAYDAAZABoBAAtnZXRfY291bnRlcgEAEGphdmEvbGFuZy9PYmplY3QBAAdDb3VudGVyAQAFdmFsdWUBAAFJAQAQamF2YS9sYW5nL1N0cmluZwEAB3ZhbHVlT2YBABUoSSlMamF2YS9sYW5nL1N0cmluZzsAIQAEAAUAAAAAAAIAAQAGAAcAAQAIAAAAIQABAAEAAAAFKrcAAbEAAAABAAkAAAAKAAIAAAAFAAQABgABAAoACwABAAgAAAAfAAEAAgAAAAeyAAK4AAOwAAAAAQAJAAAABgABAAAACQABAAwAAAACAA0=";

static const char *JAVA_INCCOUNTER_SOURCE = "round/tests/scripts/inc_counter.java";
static const char *JAVA_INCCOUNTER_CODE = "yv66vgAAADIAGwoABQAOCQAPABAKABEAEgcAEwcAFAEABjxpbml0PgEAAygpVgEABENvZGUBAA9MaW5lTnVtYmVyVGFibGUBAA5wcm9jZXNzTWVzc2FnZQEAJihMamF2YS9sYW5nL1N0cmluZzspTGphdmEvbGFuZy9TdHJpbmc7AQAKU291cmNlRmlsZQEAEGluY19jb3VudGVyLmphdmEMAAYABwcAFQwAFgAXBwAYDAAZABoBAAtpbmNfY291bnRlcgEAEGphdmEvbGFuZy9PYmplY3QBAAdDb3VudGVyAQAFdmFsdWUBAAFJAQAQamF2YS9sYW5nL1N0cmluZwEAB3ZhbHVlT2YBABUoSSlMamF2YS9sYW5nL1N0cmluZzsAIQAEAAUAAAAAAAIAAQAGAAcAAQAIAAAAIQABAAEAAAAFKrcAAbEAAAABAAkAAAAKAAIAAAAFAAQABgABAAoACwABAAgAAAArAAIAAgAAAA+yAAIEYLMAArIAArgAA7AAAAABAAkAAAAKAAIAAAAJAAgACgABAAwAAAACAA0=";

////////////////////////////////////////////////////////////
// Lua
////////////////////////////////////////////////////////////

static const char *LUA_ECHO_CODE = \
"function echo(params)\n"\
"  return params\n"\
"end";
  
static const char *LUA_SUM_CODE = \
"function sum(jsonParams)\n"\
"  local json = require(\"json\")\n"\
"  local params = json.decode(jsonParams)\n"\
"  local sum = 0\n"\
"  for i, value in pairs(params) do\n"\
"  sum = sum + value\n"\
"  end\n"\
"  return sum\n"\
"  end\n";
  
////////////////////////////////////////////////////////////
// Method Requests
////////////////////////////////////////////////////////////

static const char *JS_INVALID_FUNCTION = \
  "function echo(params) {"\
  "  return params;";

#define RPC_SET_ECHO_NAME   "echo"
#define RPC_ALIAS_HELLO_NAME "hello"
#define RPC_SET_ECHO_LANG   "js"
#define RPC_SET_ECHO_CODE   "function echo(params) {return params;}"
#define RPC_SET_ECHO_PARAMS "[1,2,3]"

////////////////////////////////////////////////
// set_method
////////////////////////////////////////////////

static const char *RPC_SET_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
   "\"method\": \"" ROUND_SYSTEM_METHOD_SET_METHOD "\","
   "\"params\": {" \
       "\"lang\": \"" RPC_SET_ECHO_LANG "\", " \
       "\"name\": \"" RPC_SET_ECHO_NAME "\", " \
       "\"code\": \"" RPC_SET_ECHO_CODE "\"" \
   "}, \"id\": 1}";

static const char *RPC_REMOVE_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUND_SYSTEM_METHOD_REMOVE_METHOD "\","
  "\"params\": {" \
  "\"name\": \"" RPC_SET_ECHO_NAME "\"" \
  "}, \"id\": 1}";
  
static const char *RPC_RUN_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
   "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
   "\"params\": " RPC_SET_ECHO_PARAMS "," \
   "\"id\": 1}";

////////////////////////////////////////////////
// Alias (Hello)
////////////////////////////////////////////////
  
static const char *RPC_SET_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUND_SYSTEM_METHOD_SET_ALIAS "\","
  "\"params\": {" \
    "\"name\": \"" RPC_ALIAS_HELLO_NAME "\", " \
    "\"method\": \"" RPC_SET_ECHO_NAME "\", " \
    "\"defaults\": \"" RPC_SET_ECHO_PARAMS "\"" \
  "}, \"id\": 1}";
  
static const char *RPC_REMOVE_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUND_SYSTEM_METHOD_REMOVE_ALIAS "\","
  "\"params\": {" \
  "\"name\": \"" RPC_ALIAS_HELLO_NAME "\"" \
  "}, \"id\": 1}";
  
static const char *RPC_RUN_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" RPC_ALIAS_HELLO_NAME "\"," \
  "\"id\": 1}";

////////////////////////////////////////////////
// Route (Hello)
////////////////////////////////////////////////

#define RPC_ECHO_HELLO_NAME   "echo_hello"
#define RPC_ECHO_HELLO_LANG   "js"
#define RPC_ECHO_HELLO_PREFIX   "Hello "
#define RPC_ECHO_HELLO_CODE   "function " RPC_ECHO_HELLO_NAME "(params) {return '" RPC_ECHO_HELLO_PREFIX "'+ params;}"
#define RPC_ECHO_HELLO_PARAM "Round"

static const char *RPC_SET_ECHO_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUND_SYSTEM_METHOD_SET_METHOD "\","
  "\"params\": {" \
  "\"lang\": \"" RPC_ECHO_HELLO_LANG "\", " \
  "\"name\": \"" RPC_ECHO_HELLO_NAME "\", " \
  "\"code\": \"" RPC_ECHO_HELLO_CODE "\"" \
  "}, \"id\": 1}";

static const char *RPC_REMOVE_ECHO_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUND_SYSTEM_METHOD_REMOVE_METHOD "\","
  "\"params\": {" \
  "\"name\": \"" RPC_ECHO_HELLO_NAME "\"" \
  "}, \"id\": 1}";

static const char *RPC_SET_ECHO_HELLO_ROUTE = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUND_SYSTEM_METHOD_SET_ROUTE "\","
  "\"params\": {" \
  "\"name\": \"" RPC_ECHO_HELLO_NAME "\"," \
  "\"src\": \"" RPC_SET_ECHO_NAME "\"," \
  "\"dest\": \"" RPC_ECHO_HELLO_NAME "\"" \
  "}, \"id\": 1}";

static const char *RPC_REMOVE_ECHO_HELLO_ROUTE = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUND_SYSTEM_METHOD_REMOVE_ROUTE "\","
  "\"params\": {" \
  "\"name\": \"" RPC_ECHO_HELLO_NAME "\"" \
  "}, \"id\": 1}";

static const char *RPC_RUN_ROUTE_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
  "\"params\": \"" RPC_ECHO_HELLO_PARAM "\"," \
  "\"id\": 1}";
  
////////////////////////////////////////////////
// RPC
////////////////////////////////////////////////

static const char *RPC_RUN_BATCH_ECHO = \
  "[" \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
  "\"params\": " RPC_SET_ECHO_PARAMS "," \
  "\"id\": 1},"
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
  "\"params\": " RPC_SET_ECHO_PARAMS "," \
  "\"id\": 1}" \
  "]";
  
static const char *RPC_SET_SETMETHOD = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"set_method\","
  "\"params\": {" \
  "\"lang\": \"" RPC_SET_ECHO_LANG "\", " \
  "\"name\": \"set_method\", " \
  "\"code\": \"" RPC_SET_ECHO_CODE "\"" \
  "}, \"id\": 1}";

RoundMethod *CreateTestMethod(const char *name, const char *lang, const char *stringCode);

class ScriptTestController {
 public:
  
  ScriptTestController() {
  }
    
  void runEchoMethodTest(RoundMethodManager *scriptMgr);
  void runSumMethodTest(RoundMethodManager *scriptMgr);
  void runCounterMethodTest(RoundMethodManager *scriptMgr);
};

}

}

#endif
