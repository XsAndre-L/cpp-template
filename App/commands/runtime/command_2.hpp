#pragma once

// #include <functional>
#include "../../util/util.hpp"
#include "../objects.hpp"

void command_2_func()
{
  println("SECOND command");
};

namespace command_2
{
  Command s_command_2_cmd = {
      "c2",
      "Test Command 2",
      "This is a test command.",
      command_2_func,
      {"2", "second"},
  };
};
