/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_TEST_NODETESTCONTROLLER_H_
#define _ROUND_TEST_NODETESTCONTROLLER_H_

#include <round/node.h>

namespace Round {
  
  class NodeTestController {
  public:
    
    NodeTestController() {
    }
    
    void runScriptManagerTest(RoundNode *node);
    void runAliasManagerTest(RoundNode *node);
    void runRouteManagerTest(RoundNode *node);
    
    void runSystemMethodTest(RoundNode *node);
    void runRpcTest(RoundNode *node);
    void runRpcTest(RoundNode **nodes, size_t nodeCnt);
    void runRpcBatchTest(RoundNode *node);
    
    void runGetEchoMethodTest(RoundNode *node, bool isJsonRpcEncodeEnabled);
    
  private:
    void runSystemEchoTest(RoundNode *node);
    void runSystemGetNodeInfoTest(RoundNode *node);
    void runSystemGetClusterInfoTest(RoundNode *node);
    void runSystemGetNetworkInfoTest(RoundNode *node);
    void runSystemRegistryTest(RoundNode *node);
    
    void runSetEchoMethodTest(RoundNode *node);
    void runPostEchoMethodTest(RoundNode *node);
    void runPostBatchEchoMethodTest(RoundNode *node);
    
    void runRpcHashTest(RoundNode **nodes, size_t nodeCnt);
  };

}

#endif