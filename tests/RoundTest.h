/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_TEST_H_
#define _ROUND_TEST_H_

#define ROUND_TEST_MAP_SIZE 10
#define ROUND_TEST_DEFAULT_WAIT_MILLI_SECOND 500

namespace Round {
  
  namespace Test {    
    int GetRandomRepeatCount(int min, int max);
    void Setup();
    void Sleep(long milliSecond = ROUND_TEST_DEFAULT_WAIT_MILLI_SECOND);

    const char *CreateJsonRpcRequestString(const char *method, const char *params);
    const char* CreateJsonRpcSetMethodRequestString(const char* lang, const char* name, const char* code);
  }
}

#endif