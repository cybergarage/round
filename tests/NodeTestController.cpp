

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
#include "ScriptTestController.h"

////////////////////////////////////////////////
// Core Functions (Script)
////////////////////////////////////////////////

void Round::NodeTestController::runScriptManagerTest(RoundNode* node)
{
  RoundJSON* json = round_json_new();
  RoundJSONObject *reqObj, *resObj;
  clock_t prevClock, postClock;
  const char* result;

  RoundError* err = round_error_new();

  // Post Node Message (Overide 'set_method' method)

  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_SETMETHOD, err));
  reqObj = round_json_poprootobject(json);
  BOOST_CHECK(reqObj);
  BOOST_CHECK(round_json_object_ismap(reqObj));

  prevClock = round_node_getclock(node);
  resObj = NULL;
  BOOST_CHECK(!round_node_postmessage(node, reqObj, &resObj, err));
  postClock = round_node_getclock(node);
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Run 'echo' method without method)

  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_ECHO, err));
  reqObj = round_json_poprootobject(json);
  BOOST_CHECK(reqObj);
  BOOST_CHECK(round_json_object_ismap(reqObj));

  prevClock = round_node_getclock(node);
  resObj = NULL;
  BOOST_CHECK(!round_node_postmessage(node, reqObj, &resObj, err));
  BOOST_CHECK_EQUAL(round_error_getdetailcode(err), ROUND_RPC_ERROR_CODE_METHOD_NOT_FOUND);
  postClock = round_node_getclock(node);
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Set 'echo' method)

  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_ECHO, err));
  reqObj = round_json_poprootobject(json);
  BOOST_CHECK(reqObj);
  BOOST_CHECK(round_json_object_ismap(reqObj));

  prevClock = round_node_getclock(node);
  resObj = NULL;
  BOOST_CHECK(round_node_postmessage(node, reqObj, &resObj, err));
  postClock = round_node_getclock(node);
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Run 'echo' method)

  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_ECHO, err));
  reqObj = round_json_poprootobject(json);
  BOOST_CHECK(reqObj);
  BOOST_CHECK(round_json_object_ismap(reqObj));

  prevClock = round_node_getclock(node);
  resObj = NULL;
  BOOST_CHECK(round_node_postmessage(node, reqObj, &resObj, err));
  postClock = round_node_getclock(node);
  BOOST_CHECK(prevClock < postClock);

  result = NULL;
  BOOST_CHECK(round_json_rpc_getresultstring(resObj, &result));
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(result, RPC_SET_ECHO_PARAMS);

  // Post Node Message (Override 'echo' method)

  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_ECHO, err));
  reqObj = round_json_poprootobject(json);
  BOOST_CHECK(reqObj);
  BOOST_CHECK(round_json_object_ismap(reqObj));

  prevClock = round_node_getclock(node);
  resObj = NULL;
  BOOST_CHECK(round_node_postmessage(node, reqObj, &resObj, err));
  postClock = round_node_getclock(node);
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Run 'echo' method)

  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_ECHO, err));
  reqObj = round_json_poprootobject(json);
  BOOST_CHECK(reqObj);
  BOOST_CHECK(round_json_object_ismap(reqObj));

  prevClock = round_node_getclock(node);
  resObj = NULL;
  BOOST_CHECK(round_node_postmessage(node, reqObj, &resObj, err));
  postClock = round_node_getclock(node);
  BOOST_CHECK(prevClock < postClock);

  result = NULL;
  BOOST_CHECK(round_json_rpc_getresultstring(resObj, &result));
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(result, RPC_SET_ECHO_PARAMS);

  // Post Node Message (Remove 'echo' method)

  BOOST_CHECK(round_json_parse(json, Test::RPC_REMOVE_ECHO, err));
  reqObj = round_json_poprootobject(json);
  BOOST_CHECK(reqObj);
  BOOST_CHECK(round_json_object_ismap(reqObj));

  prevClock = round_node_getclock(node);
  resObj = NULL;
  BOOST_CHECK(round_node_postmessage(node, reqObj, &resObj, err));
  postClock = round_node_getclock(node);
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Run 'echo' method)

  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_ECHO, err));
  reqObj = round_json_poprootobject(json);
  BOOST_CHECK(reqObj);
  BOOST_CHECK(round_json_object_ismap(reqObj));

  prevClock = round_node_getclock(node);
  resObj = NULL;
  BOOST_CHECK(!round_node_postmessage(node, reqObj, &resObj, err));
  BOOST_CHECK_EQUAL(round_error_getdetailcode(err), ROUND_RPC_ERROR_CODE_METHOD_NOT_FOUND);
  postClock = round_node_getclock(node);

  BOOST_CHECK(prevClock < postClock);
}

////////////////////////////////////////////////
// Core Functions (Alias)
////////////////////////////////////////////////

void Round::NodeTestController::runAliasManagerTest(RoundNode* node)
{
  /*
  NodeRequestParser reqParser;
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  Error error;
  std::string result;
  
  // Set 'echo' method
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_ECHO, err));
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
  
  // Set 'hello' alias
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_HELLO, err));
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));

  // Run 'hello' alias
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_HELLO, err));
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK(result.compare(RPC_SET_ECHO_PARAMS) == 0);
  
  // Remove 'hello' alias
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_REMOVE_HELLO, err));
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
 */
}

////////////////////////////////////////////////
// Core Functions (Route)
////////////////////////////////////////////////

void Round::NodeTestController::runRouteManagerTest(RoundNode* node)
{
  /*
  NodeRequestParser reqParser;
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  Error error;
  std::string result;
  
  // Post Node Message (Set 'echo' method)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_ECHO, err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
  
  // Post Node Message (Set 'echo_hello' method)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_ECHO_HELLO, err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
  
  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_ROUTE_ECHO, err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK(result.compare("\"" RPC_ECHO_HELLO_PARAM "\"") == 0);

  // Post Node Message (Set 'echo_hello' route)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_ECHO_HELLO_ROUTE, err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
  
  // Post Node Message (Run 'echo' + 'echo_hello' method)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_ROUTE_ECHO, err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
  BOOST_CHECK(nodeRes.getResult(&result));
  BOOST_CHECK(result.compare("\"" RPC_ECHO_HELLO_PREFIX  RPC_ECHO_HELLO_PARAM "\"") == 0);
  
  // Post Node Message (Remove 'echo_hello' route)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_REMOVE_ECHO_HELLO_ROUTE, err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));

  // Post Node Message (Remove 'echo' method)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_REMOVE_ECHO, err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));

  // Post Node Message (Remove 'echo_hello' method)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_REMOVE_ECHO_HELLO, err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, err));
 */
}

////////////////////////////////////////////////
// Basic Functions
////////////////////////////////////////////////

void Round::NodeTestController::runRpcBatchTest(RoundNode* node)
{
  // echo (Add)
  runPostBatchEchoMethodTest(node);
}

void Round::NodeTestController::runSetEchoMethodTest(RoundNode* node)
{
  /*
  Error err;
  
  BOOST_CHECK(node->isAlive(&err));
  
  // Post Node Message (Set 'echo' method)
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  clock_t prevClock, postClock;
  std::string result;
  
  NodeRequestParser reqParser;
  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_ECHO, &err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &err));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
   */
}

void Round::NodeTestController::runPostEchoMethodTest(RoundNode* node)
{
  /*
  Error err;
  
  BOOST_CHECK(node->isAlive(&err));
  
  // Post Node Message (Run 'echo' method)
  
  NodeRequestParser reqParser;
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  clock_t prevClock, postClock;
  std::string result;
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_ECHO, &err));
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

void Round::NodeTestController::runPostBatchEchoMethodTest(RoundNode* node)
{
  /*
  Error err;
  
  BOOST_CHECK(node->isAlive(&err));
  
  // Post Node Message (Run 'echo' method)
  
  NodeRequestParser reqParser;
  NodeBatchRequest *nodeReq;
  NodeBatchResponse nodeRes;
  clock_t prevClock, postClock;
  std::string result;
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_BATCH_ECHO, &err));
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

void Round::NodeTestController::runGetEchoMethodTest(RoundNode* node, bool isJsonRpcEncodeEnabled)
{
  /*
  Error err;
  
  BOOST_CHECK(node->isAlive(&err));
  
  // Post Node Message (Set 'echo' method)
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  clock_t prevClock, postClock;
  std::string result;
  
  NodeRequestParser reqParser;
  BOOST_CHECK(round_json_parse(json, Test::RPC_SET_ECHO, &err));
  BOOST_CHECK(reqParser.getRootObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getRootObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->getMessage(nodeReq, &nodeRes, &err, isJsonRpcEncodeEnabled));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(round_json_parse(json, Test::RPC_RUN_ECHO, &err));
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

void Round::NodeTestController::runRpcHashTest(RoundNode** nodes, size_t nodeCnt)
{
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

void Round::NodeTestController::runRpcTest(RoundNode** nodes, size_t nodeCnt)
{
  runRpcHashTest(nodes, nodeCnt);
}

////////////////////////////////////////////////
// System Methods
////////////////////////////////////////////////

void Round::NodeTestController::runSystemEchoTest(RoundNode* node)
{
  /*
  Error err;
  BOOST_CHECK(node->isAlive(&err));
   */
}

void Round::NodeTestController::runSystemGetNodeInfoTest(RoundNode* node)
{
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

void Round::NodeTestController::runSystemGetClusterInfoTest(RoundNode* node)
{
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

void Round::NodeTestController::runSystemGetNetworkInfoTest(RoundNode* node)
{
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

void Round::NodeTestController::runSystemRegistryTest(RoundNode* node)
{
#define REGISTRY_TEST_CNT 10

  char key[32], val[32];

  RoundError* err = round_error_new();

  for (int n = 0; n < REGISTRY_TEST_CNT; n++) {
    snprintf(key, sizeof(key), "/key%d", n);
    snprintf(val, sizeof(val), "val%d", n);
    BOOST_CHECK(round_node_setregistry(node, key, val, err));
  }

  for (int n = 0; n < REGISTRY_TEST_CNT; n++) {
    snprintf(key, sizeof(key), "/key%d", n);
    snprintf(val, sizeof(val), "val%d", n);
    char* keyVal = NULL;
    BOOST_CHECK(round_node_getregistry(node, key, &keyVal, err));
    BOOST_CHECK(keyVal);
    if (!keyVal)
      continue;
    BOOST_CHECK_EQUAL(keyVal, key);
    free(keyVal);
  }

  for (int n = 0; n < REGISTRY_TEST_CNT; n++) {
    snprintf(key, sizeof(key), "/key%d", n);
    BOOST_CHECK(round_node_removeregistry(node, key, err));
  }

  round_error_delete(err);
}

void Round::NodeTestController::runSystemMethodTest(RoundNode* node)
{
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

void Round::NodeTestController::runRpcTest(RoundNode* node)
{
  /*
  // echo (Add)
  runSetEchoMethodTest(node);

  // echo (POST)
  runPostEchoMethodTest(node);

  // echo (GET) only RemoteNode
  RemoteNode *remoteNode = dynamic_cast<RemoteNode *>(node);
  if (remoteNode) {
    runGetEchoMethodTest(remoteNode, true);
  }
  */
}
