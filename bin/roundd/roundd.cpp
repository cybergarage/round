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
  // Setup Server

  RoundServer* server = round_server_new();

  // Parse options

  if (round_server_setarguments(server, argc, argv)) {
    round_server_printusage(server);
    exit(EXIT_FAILURE);
  }

  // Setup deamon

  if (round_server_isdeamonmode(server)) {
    int pid = fork();
    if (pid < 0)
      exit(EXIT_FAILURE);

    if (0 < pid)
      exit(EXIT_SUCCESS);

    if (setsid() < 0)
      exit(EXIT_FAILURE);

    if (chdir("/") < 0) {
      exit(EXIT_FAILURE);
    }

    umask(0);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }

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
