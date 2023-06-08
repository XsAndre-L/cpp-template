
#pragma once

#include <functional>
#include <array>

#include "../util/util.hpp"
#include "objects.hpp"

// COMMANDS
#include "runtime/test_cmd.hpp"
#include "runtime/command_2.hpp"

std::string getCommand()
{
  std::string command;
  std::cout << BLUE << "> " << RESET;
  std::cin >> command;
  return command;
}

std::array<Command, 2> commands = {test_cmd::s_test_cmd, command_2::s_command_2_cmd};

void help_cmd_func()
{
  print(red("----------") + "HELP" + red("----------\n"));
  for (size_t i = 0; i < commands.size(); i++)
  {
    const Command current = commands[i];

    print(current.cmd + " - ", GREEN);
    print(current.name + " ");
    print(current.description);
    std::string aliases;
    for (const auto &alias : current.aliases)
    {
      aliases += alias + " ";
    }
    println();
    println("Aliases: " + aliases, YELLOW);
    println();
    /* code */
  }
}

bool exec_cmd(const std::string &input)
{
  const std::string checked_input = toLowerCase(input);

  // Check important functions
  if (checked_input == "exit")
    return EXIT;

  if (checked_input == "help")
  {
    help_cmd_func();
    return CONTINUE;
  }

  for (const auto &command : commands)
  {
    // Check if input match command
    if (checked_input == command.cmd)
    {
      command.action();
      return CONTINUE;
    }

    for (const auto &alias : command.aliases)
    {
      if (checked_input == alias)
      {
        command.action();
        return CONTINUE;
      }
    }
  }
  println("Command not found!", RED);
  return CONTINUE;
}