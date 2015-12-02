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

#include <round/Round.h>
//#include <round/ui/Console.h>

// typedef std::map<std::string,std::string> RounddOptionsDictionary;

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

  Round::Console::Server server;
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

  // Start server

  if (server.start(&err) == false) {
    Round::RoundLog(err);
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
    case SIGKILL:
      {
        server.stop(&err);
        isRunnging = false;
      }
      break;
    case SIGHUP:
      {
        if (server.start(&err) == false) {
          Round::RoundLog(err);
          exit(EXIT_FAILURE);
        }
      }
      break;
    }
  }
  */

  return EXIT_SUCCESS;
}
