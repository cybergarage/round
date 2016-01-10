/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <unistd.h>
#include <round/server_internal.h>

/****************************************
 * round_server_setarguments
 ****************************************/

void round_server_printusage(RoundServer* server)
{
  printf("USAGE: roundd [options]\n");
  printf("\n");
  printf("OPTIONS:");
  printf("\n");
}

/****************************************
 * round_server_setarguments
 ****************************************/

bool round_server_setarguments(RoundServer* server, int argc, char* argv[])
{
  /*
   Round::Error err;
   
   // Option parameters
   */

  bool deamonMode = true;
  bool verboseMode = false;
  const char* configFilename = "";
  const char* bindAddr = "";
  const char* bindCluster = "";
  int bindPort = 0;

  /*
   server.setFirstArgument(argv[0]);
   */

  // Parse options

  int ch;
  while ((ch = getopt(argc, argv, "fhvp:")) != -1) {
    switch (ch) {
    case 'v': {
      verboseMode = true;
    } break;
    case 'f': {
      round_server_setdeamonmode(server, false);
      deamonMode = false;
    } break;
    case 'p': {
      bindPort = atoi(optarg);
    } break;
    case 'h':
    default:
      return false;
    }
  }

  // Setup Logger

  /*
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
   */

  /*
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
   */

  /*
   if (0 < bindPort) {
   if (!server.setBindPort(bindPort, &err)) {
   Round::RoundLog(err);
   exit(EXIT_FAILURE);
   }
   }
   */

  /*
   if (0 < bindCluster.length()) {
   if (!server.setCluster(bindCluster, &err)) {
   Round::RoundLog(err);
   exit(EXIT_FAILURE);
   }
   }
   */

  return true;
}
