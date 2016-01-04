/*****************************************************************
*
* Round for C
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <iostream>
#include <map>

//#include <boost/algorithm/string.hpp>

#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <histedit.h>

#include <round/client.h>
//#include <round/ui/Console.h>

static const std::string ROUND_CERR_PREFIX = "Error : ";
static const std::string ROUND_UNKNOWN_COMMAND_MSG = "Unrecognized command ";
static const std::string ROUND_CLINET_DOMAIN_SOCKET = "/tmp/round";

// static Round::Console::Client *gConsoleClient;

const char* round_prompt(EditLine* e)
{
  // return gConsoleClient->getPromptName();
  return "";
}

/*
void round_print_boot_message(Round::Console::Client &client) {
  std::string bootMessage;
  client.getBootMessage(bootMessage);
  std::cout << bootMessage << std::endl;
}
*/

bool round_exec_console_command(RoundClient* client, const char* cmd, int argc, char* argv[])
{
  /*
  Round::Console::Message msg;
  Round::Error err;

  if (client.execConsoleCommand(input, &msg, &err)) {
    if (0 < msg.length()) {
      std::cout << msg << std::endl;
    }
    return true;
  }

  std::string errMsg = err.getDetailMessage();
  if (0 < errMsg.length()) {
    std::cerr << ROUND_CERR_PREFIX << errMsg << "'" << std::endl;
  }
   */

  return false;
}

/*
bool exec_rpc_command(Round::Console::Client &client, const
Round::Console::Input &input) {
  Round::Console::Message msg;
  Round::Error err;

  if (client.execRPCCommand(input, &msg, &err)) {
    if (0 < msg.length()) {
      std::cout << msg << std::endl;
    }
    return true;
  }

  std::string errMsg = err.getDetailMessage();
  if (errMsg.length() <= 0) {
    errMsg = err.getMessage();
  }
  if (0 < errMsg.length()) {
    std::cerr << ROUND_CERR_PREFIX << errMsg << "'" << std::endl;
  }

  return false;
}

int round_exec_shell(Round::Console::Client &client)
{
  Round::Error error;

  // Boot Message

  round_print_boot_message(client);

  // Initialize the EditLine

  EditLine *el = el_init(client.getProgramName(), stdin, stdout, stderr);
  el_set(el, EL_PROMPT, &round_prompt);
  el_set(el, EL_EDITOR, "vi");

  // Initialize the history

  HistEvent ev;
  History *inputHistory = history_init();
  history(inputHistory, &ev, H_SETSIZE, 1024);
  el_set(el, EL_HIST, history, inputHistory);

  Round::Console::Input input;

  while (true) {
    int readCount = 0;
    std::string inputLine = el_gets(el, &readCount);

    if (readCount <= 0)
      continue;

    if ((readCount == 1) && inputLine[0] == '\n')
      continue;

    boost::trim(inputLine);
    history(inputHistory, &ev, H_ENTER, inputLine.c_str());

    input.parse(inputLine);

    if (client.isQuitCommand(input))
      break;

    if (client.isRPCCommand(input)) {
      exec_rpc_command(client, input);
      continue;
    }

    if (!client.isConsoleCommand(input)) {
      std::cerr << ROUND_UNKNOWN_COMMAND_MSG << " '" << inputLine << "'" <<
std::endl;
      continue;
    }

    round_exec_console_command(client, input);
  }

  history_end(inputHistory);
  el_end(el);

  return EXIT_SUCCESS;
}

 */

int main(int argc, char* argv[])
{
  RoundError* err = round_error_new();

  // Setup Client

  RoundClient* client = round_client_new();
  if (!client)
    return EXIT_FAILURE;

  /*
  // Parse command line options

  bool deamonMode = false;
  std::string remoteHost;

  int ch;
  while ((ch = getopt(argc, argv, "r:hd")) != -1) {
    switch (ch) {
      case 'r':
        {
          remoteHost = optarg;
        }
        break;
      case 'd':
        {
          deamonMode = true;
        }
        break;
      case 'h':
      default:
        {
          client.usage();
          exit(EXIT_SUCCESS);
        }
    }
  }
  argc -= optind;
  argv += optind;

  // Check command

  if (argc <= 0) {
    client.usage();
    exit(EXIT_FAILURE);
  }

  std::string firstArg = argv[0];
*/
  // Start Client

  if (!round_client_start(client))
    return EXIT_FAILURE;

  if (!round_client_search(client))
    return EXIT_FAILURE;
  /*
  if (0 < remoteHost.length()) {
    client.updateClusterFromRemoteNode(remoteHost, &error);
  }

  // Execute shell

  if (client.isShellCommand(firstArg)) {
    return round_exec_shell(client);
  }
*/
  // Exec command

  if (!round_exec_console_command(client, argv[0], (argc - 1), argv++))
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
