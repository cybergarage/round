/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string>
#include <map>
#include <iostream>

#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <histedit.h>
#include <signal.h>

#include <round/const.h>
#include <round/server.h>

//#include <round/ui/Console.h>

// typedef std::map<std::string,std::string> RounddOptionsDictionary;

/****************************************
 * SetupServer
 ****************************************/

void AddTestMethods(RoundServer* server)
{
#define SET_KEY_NAME "set_key"
#define GET_KEY_NAME "get_key"
#define REMOVE_KEY_NAME "remove_key"

  static const char* SETKEY_CODE = "function " SET_KEY_NAME "(params) {return " ROUND_SYSTEM_METHOD_SET_REGISTRY "(params);}";
  static const char* GETKEY_CODE = "function " GET_KEY_NAME "(params) {return " ROUND_SYSTEM_METHOD_GET_REGISTRY "(params);}";
  static const char* REMOVEKEY_CODE = "function " REMOVE_KEY_NAME "(params) {return " ROUND_SYSTEM_METHOD_REMOVE_REGISTRY "(params);}";

  RoundLocalNode* node = round_server_getlocalnode(server);
  RoundError* err = round_error_new();

  // Set '*_key' method

  round_node_setmethod(node, ROUND_SCRIPT_LANGUAGE_JS, SET_KEY_NAME, SETKEY_CODE, err);
  round_node_setmethod(node, ROUND_SCRIPT_LANGUAGE_JS, GET_KEY_NAME, GETKEY_CODE, err);
  round_node_setmethod(node, ROUND_SCRIPT_LANGUAGE_JS, REMOVE_KEY_NAME, REMOVEKEY_CODE, err);

  round_error_delete(err);
}

void SetupServer(RoundServer* server)
{
  AddTestMethods(server);
}

/****************************************
 * main
 ****************************************/

int main(int argc, char* argv[])
{
  /*
  Round::Error err;

  // Option parameters

  bool deamonMode = true;
  bool verboseMode = false;
  std::string configFilename = "";
  std::string bindAddr = "";
  std::string bindCluster = "";
  int bindPort = 0;

  // Setup Server
   */

  RoundServer* server = round_server_new();

  /*
  server.setFirstArgument(argv[0]);

  // Parse options

  int ch;
  while ((ch = getopt(argc, argv, "fhvc:i:p:s:")) != -1) {
    switch (ch) {
    case 'v':
      {
        verboseMode = true;
      }
      break;
    case 'f':
      {
        deamonMode = false;
      }
      break;
    case 'c':
      {
        bindCluster = optarg;
      }
      break;
    case 'i':
      {
        bindAddr = optarg;
      }
      break;
    case 'p':
      {
        bindPort = atoi(optarg);
      }
      break;
    case 's':
      {
        configFilename = optarg;
      }
      break;
    case 'h':
    default:
      {
        server.usage();
        exit(EXIT_SUCCESS);
      }
    }
   }

  argc -= optind;
  argv += optind;

  // Setup deamon

  if (deamonMode) {
    int pid = fork();
    if (pid < 0)
      exit(EXIT_FAILURE);

    if (0 < pid)
      exit(EXIT_SUCCESS);

    if (setsid() < 0)
      exit(EXIT_FAILURE);

    if ( chdir("/") < 0 ) {
      exit(EXIT_FAILURE);
    }

    umask(0);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }

  // Setup Logger

  Round::Logger *logger = server.getLogger();
  logger->setLevel((verboseMode ? Round::LoggerLevel::TRACE :
  Round::LoggerLevel::INFO));

  if (deamonMode) {
    std::string logFilename;
    if (server.getLogFilename(&logFilename, &err)) {
      Round::LoggerFileTarget *fileTarget = new Round::LoggerStdFileTarget();
      if (fileTarget->open(logFilename)) {
        logger->addTarget(fileTarget);
      }
      else
        delete fileTarget;
    }
  }
  else {
    logger->addTarget(new Round::LoggerStdoutTarget());
    logger->addTarget(new Round::LoggerStderrTarget());
  }

  // Setup configuration

  if (0 < configFilename.length()) {
    if (!server.loadConfigFromString(configFilename, &err)) {
      Round::RoundLog(err);
      exit(EXIT_FAILURE);
    }
  }

  if (0 < bindAddr.length()) {
    if (!server.setBindAddress(bindAddr, &err)) {
      Round::RoundLog(err);
      exit(EXIT_FAILURE);
    }
  }

  if (0 < bindPort) {
    if (!server.setBindPort(bindPort, &err)) {
      Round::RoundLog(err);
      exit(EXIT_FAILURE);
    }
  }

  if (0 < bindCluster.length()) {
    if (!server.setCluster(bindCluster, &err)) {
      Round::RoundLog(err);
      exit(EXIT_FAILURE);
    }
  }
*/

  // Setup server

  SetupServer(server);

  // Start server

  if (!round_server_start(server)) {
    exit(EXIT_FAILURE);
  }

  bool isRunnging = true;

  while (isRunnging) {
    sigset_t sigSet;
    if (sigfillset(&sigSet) != 0)
      break;

    int sigNo;
    if (sigwait(&sigSet, &sigNo) != 0)
      break;

    switch (sigNo) {
    case SIGTERM:
    case SIGINT:
    case SIGKILL: {
      round_server_stop(server);
      isRunnging = false;
    } break;
    case SIGHUP: {
      if (!round_server_start(server)) {
        exit(EXIT_FAILURE);
      }
    } break;
    }
  }

  return EXIT_SUCCESS;
}
