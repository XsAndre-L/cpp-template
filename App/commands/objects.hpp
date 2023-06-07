#pragma once

#include <string>
#include <functional>

struct Command
{
  std::string cmd;
  std::string alias;
  std::string name;
  std::string description;
  std::function<void()> action;
};