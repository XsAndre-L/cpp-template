#pragma once

#include <string>
#include <functional>
#include <array>

struct Command
{
  std::string cmd;
  std::string name;
  std::string description;
  std::function<void()> action;
  std::array<std::string, 2> aliases;
};