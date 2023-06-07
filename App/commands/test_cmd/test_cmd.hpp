#pragma once

// #include <functional>

#include "../../util/util.h"
#include "../objects.hpp"

void test_cmd_func()
{
  println("Hello World!");
};

namespace test_cmd
{
  Command s_test_cmd = {
      "test",
      "t",
      "Test Command",
      "This is a test command.",
      test_cmd_func};
};
