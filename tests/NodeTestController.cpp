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

#include <sstream>
#include <string.h>

#include "NodeTestController.h"

////////////////////////////////////////////////
// Core Functions (Script)
////////////////////////////////////////////////

void Round::NodeTestController::runScriptManagerTest(RoundNode *node) {
  /*
  NodeRequestParser reqParser;
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  Error error;
  clock_t prevClock, postClock;
  std::string result;
  
  // Post Node Message (Overide 'set_method' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_SETMETHOD, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  // Post Node Message (Run 'echo' method without method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK(error.getDetailCode() == RPC::JSON::ErrorCodeMethodNotFound);
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  // Post Node Message (Set 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);

  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK(result.compare(RPC_SET_ECHO_PARAMS) == 0);
  
  // Post Node Message (Override 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK(result.compare(RPC_SET_ECHO_PARAMS) == 0);

  // Post Node Message (Remove 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_REMOVE_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);

  prevClock = node->getLocalClock();
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK(error.getDetailCode() == RPC::JSON::ErrorCodeMethodNotFound);
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
*/
}

////////////////////////////////////////////////
// Core Functions (Alias)
////////////////////////////////////////////////

void Round::NodeTestController::runAliasManagerTest(RoundNode *node) {
/*
  NodeRequestParser reqParser;
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  Error error;
  std::string result;
  
  // Set 'echo' method
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO, &error));
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  
  // Set 'hello' alias
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_HELLO, &error));
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));

  // Run 'hello' alias
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_HELLO, &error));
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK(result.compare(RPC_SET_ECHO_PARAMS) == 0);
  
  // Remove 'hello' alias
  
  BOOST_CHECK(reqParser.parse(Test::RPC_REMOVE_HELLO, &error));
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
 */
}

////////////////////////////////////////////////
// Core Functions (Route)
////////////////////////////////////////////////

void Round::NodeTestController::runRouteManagerTest(RoundNode *node) {
/*
  NodeRequestParser reqParser;
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  Error error;
  std::string result;
  
  // Post Node Message (Set 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  
  // Post Node Message (Set 'echo_hello' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO_HELLO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  
  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ROUTE_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK(result.compare("\"" RPC_ECHO_HELLO_PARAM "\"") == 0);

  // Post Node Message (Set 'echo_hello' route)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO_HELLO_ROUTE, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  
  // Post Node Message (Run 'echo' + 'echo_hello' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ROUTE_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK(result.compare("\"" RPC_ECHO_HELLO_PREFIX  RPC_ECHO_HELLO_PARAM "\"") == 0);
  
  // Post Node Message (Remove 'echo_hello' route)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_REMOVE_ECHO_HELLO_ROUTE, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));

  // Post Node Message (Remove 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_REMOVE_ECHO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));

  // Post Node Message (Remove 'echo_hello' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_REMOVE_ECHO_HELLO, &error));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
 */
}

////////////////////////////////////////////////
// Basic Functions
////////////////////////////////////////////////

void Round::NodeTestController::runRpcBatchTest(RoundNode *node) {
  // echo (Add)
  runPostBatchEchoMethodTest(node);
}

void Round::NodeTestController::runSetEchoMethodTest(RoundNode *node) {
  /*
  Error err;
  
  BOOST_CHECK(node->isAlive(&err));
  
  // Post Node Message (Set 'echo' method)
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  clock_t prevClock, postClock;
  std::string result;
  
  NodeRequestParser reqParser;
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO, &err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &err));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
   */
}
  
void Round::NodeTestController::runPostEchoMethodTest(RoundNode *node) {
  /*
  Error err;
  
  BOOST_CHECK(node->isAlive(&err));
  
  // Post Node Message (Run 'echo' method)
  
  NodeRequestParser reqParser;
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  clock_t prevClock, postClock;
  std::string result;
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO, &err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &err));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK_EQUAL(result.compare(RPC_SET_ECHO_PARAMS), 0);
   */
}

void Round::NodeTestController::runPostBatchEchoMethodTest(RoundNode *node) {
  /*
  Error err;
  
  BOOST_CHECK(node->isAlive(&err));
  
  // Post Node Message (Run 'echo' method)
  
  NodeRequestParser reqParser;
  NodeBatchRequest *nodeReq;
  NodeBatchResponse nodeRes;
  clock_t prevClock, postClock;
  std::string result;
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_BATCH_ECHO, &err));
  BOOST_CHECK(reqParser.getRootObject()->isArray());
  nodeReq = dynamic_cast<NodeBatchRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &err));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  //BOOST_CHECK(nodeRes.getResult(&result));
  //BOOST_CHECK_EQUAL(result.compare(RPC_SET_ECHO_PARAMS), 0);
   */
}

void Round::NodeTestController::runGetEchoMethodTest(RoundNode *node, bool isJsonRpcEncodeEnabled) {
  /*
  Error err;
  
  BOOST_CHECK(node->isAlive(&err));
  
  // Post Node Message (Set 'echo' method)
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  clock_t prevClock, postClock;
  std::string result;
  
  NodeRequestParser reqParser;
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO, &err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->getMessage(nodeReq, &nodeRes, &err, isJsonRpcEncodeEnabled));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO, &err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->getMessage(nodeReq, &nodeRes, &err, isJsonRpcEncodeEnabled));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);

  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK_EQUAL(result.compare(RPC_SET_ECHO_PARAMS), 0);
   */
}

void Round::NodeTestController::runRpcHashTest(RoundNode **nodes, size_t nodeCnt) {
  /*
  Error err;
  
  std::vector<std::string> nodeHashes;
  for (size_t n=0; n<nodeCnt; n++) {
    std::string nodeHash;
    BOOST_CHECK(nodes[n]->getHashCode(&nodeHash));
    nodeHashes.push_back(nodeHash);
  }
  
  for (size_t i=0; i<nodeCnt; i++) {
    size_t successCnt = 0;
    for (size_t j=0; j<nodeCnt; j++) {
      SystemEchoRequest nodeReq;
      nodeReq.setDest(nodeHashes.at(j));
      NodeResponse nodeRes;
      if (nodes[i]->postMessage(&nodeReq, &nodeRes, &err)) {
        successCnt++;
      }
      else {
        BOOST_CHECK(err.getDetailCode() == RPC::JSON::ErrorCodeMovedPermanently);
      }
    }
    BOOST_CHECK_EQUAL(successCnt, 1);
  }
   */
}

void Round::NodeTestController::runRpcTest(RoundNode **nodes, size_t nodeCnt) {
  runRpcHashTest(nodes, nodeCnt);
}

////////////////////////////////////////////////
// System Methods
////////////////////////////////////////////////

void Round::NodeTestController::runSystemEchoTest(RoundNode *node) {
  /*
  Error err;
  BOOST_CHECK(node->isAlive(&err));
   */
}

void Round::NodeTestController::runSystemGetNodeInfoTest(RoundNode *node) {
  /*
  Error err;
  std::string jsonString;
  
  // Node information
  
  std::string nodeIp;
  BOOST_CHECK(node->getRequestAddress(&nodeIp, &err));
  
  int nodePort;
  BOOST_CHECK(node->getRequestPort(&nodePort, &err));
  
  std::string nodeCluster;
  BOOST_CHECK(node->getClusterName(&nodeCluster, &err));
  
  std::string nodeHash;
  BOOST_CHECK(node->getHashCode(&nodeHash));
  
  // Response information
  
  SystemGetNodeInfoRequest nodeReq;
  NodeResponse nodeRes;
  
  nodeReq.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  BOOST_CHECK(node->postMessage(&nodeReq, &nodeRes, &err));
  
  nodeRes.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  SystemGetNodeInfoResponse sysRes(&nodeRes);
  
  std::string resIp;
  BOOST_CHECK(sysRes.getAddress(&resIp));
  
  int resPort;
  BOOST_CHECK(sysRes.getPort(&resPort));
  
  std::string resCluster;
  BOOST_CHECK(sysRes.getCluster(&resCluster));
  
  std::string resHash;
  BOOST_CHECK(sysRes.getHash(&resHash));
  
  // Compare information
  
  BOOST_CHECK_EQUAL(nodeIp.compare(resIp), 0);
  BOOST_CHECK_EQUAL(nodePort, resPort);
  BOOST_CHECK_EQUAL(nodeCluster.compare(resCluster), 0);
  BOOST_CHECK_EQUAL(nodeHash.compare(resHash), 0);
   */
}

void Round::NodeTestController::runSystemGetClusterInfoTest(RoundNode *node) {
  /*
  Error err;
  std::string jsonString;
  
  // Node information
  
  std::string nodeClusterName;
  BOOST_CHECK(node->getClusterName(&nodeClusterName, &err));
  
  // Response information
  
  SystemGetClusterInfoRequest nodeReq;
  NodeResponse nodeRes;
  
  nodeReq.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  BOOST_CHECK(node->postMessage(&nodeReq, &nodeRes, &err));
  
  nodeRes.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  // Check Response
  
  SystemGetClusterInfoResponse sysRes(&nodeRes);
  
  Cluster cluster;
  BOOST_CHECK(sysRes.getCluster(&cluster));
  BOOST_CHECK(cluster.hasNode(node));
  BOOST_CHECK_EQUAL(nodeClusterName.compare(cluster.getName()), 0);
   */
}

void Round::NodeTestController::runSystemGetNetworkInfoTest(RoundNode *node) {
/*
  Error err;
  std::string jsonString;
  
  // Node information
  
  std::string nodeClusterName;
  BOOST_CHECK(node->getClusterName(&nodeClusterName, &err));
  
  // Response information
  
  SystemGetNetworkInfoRequest nodeReq;
  NodeResponse nodeRes;
  
  nodeReq.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  BOOST_CHECK(node->postMessage(&nodeReq, &nodeRes, &err));
  
  nodeRes.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  // Check Response
  
  SystemGetNetworkInfoResponse sysRes(&nodeRes);
  
  ClusterList clusterList;
  BOOST_CHECK(sysRes.getClusters(&clusterList));
  BOOST_CHECK(clusterList.hasCluster(nodeClusterName));
  
  Cluster *cluster = clusterList.getCluster(nodeClusterName);
  BOOST_CHECK(cluster);
  BOOST_CHECK(cluster->hasNode(node));
 */
}

void Round::NodeTestController::runSystemRegistryTest(RoundNode *node) {
  /*
  Error err;
  
  string key = "key";
  string value;
  string valueBuf;
  
  BOOST_CHECK_EQUAL(node->getRegistry(key, &valueBuf, &err), false);
  
  value = "hello";
  BOOST_CHECK(node->setRegistry(key, value, &err));
  BOOST_CHECK_EQUAL(node->getRegistry(key, &valueBuf, &err), true);
  BOOST_CHECK_EQUAL(valueBuf.compare(value), 0);
  
  value = "world";
  BOOST_CHECK(node->setRegistry(key, value, &err));
  BOOST_CHECK_EQUAL(node->getRegistry(key, &valueBuf, &err), true);
  BOOST_CHECK_EQUAL(valueBuf.compare(value), 0);
  
  */
}

void Round::NodeTestController::runSystemMethodTest(RoundNode *node) {
  // _echo()
  runSystemEchoTest(node);
  
  // get_node_state()
  runSystemGetNodeInfoTest(node);
  
  // get_cluster_state()
  runSystemGetClusterInfoTest(node);
  
  // get_network_state()
  runSystemGetNetworkInfoTest(node);
  
  // set_registry() and get_registry()
  runSystemRegistryTest(node);
}

void Round::NodeTestController::runRpcTest(RoundNode *node) {
  // echo (Add)
  runSetEchoMethodTest(node);
  
  // echo (POST)
  runPostEchoMethodTest(node);
/*
  // echo (GET) only RemoteNode
  RemoteNode *remoteNode = dynamic_cast<RemoteNode *>(node);
  if (remoteNode) {
    runGetEchoMethodTest(remoteNode, true);
  }
*/
}

