#pragma once

// #include <functional>
#include "../../util/util.hpp"
#include "../objects.hpp"

void test_cmd_func()
{
  println("Hello World!");
};

namespace test_cmd
{
  Command s_test_cmd = {
      "test",
      "Test Command",
      "This is a test command.",
      test_cmd_func,
      {"t"},
  };
};
