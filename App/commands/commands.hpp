
#pragma once

#include <functional>
#include <array>

#include "../util/util.h"
#include "objects.hpp"

// COMMANDS
#include "test_cmd/test_cmd.hpp"

std::array<Command, 1> commands = {test_cmd::s_test_cmd};

void help_cmd_func()
{
  print("-------- ", RED);
  print("HELP", RESET);
  print(" --------\n", RED);
  for (size_t i = 0; i < commands.size(); i++)
  {
    const Command current = commands[i];

    print(current.cmd + " - ", GREEN);
    print(current.name + " ");
    print(current.description);
    println("Aliases: " + current.alias);
    println();
    /* code */
  }
}

void exec_cmd(const std::string &cmd)
{
  for (const auto &command : commands)
  {
    if (cmd == command.cmd || cmd == command.alias)
    {
      command.action();
      return;
    }

    println("Command not found!", RED);
  }
}