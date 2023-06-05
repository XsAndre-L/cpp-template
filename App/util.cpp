#include "util.h"

std::string getCommand()
{
  std::string command;
  std::cout << BLUE << "Enter command: " << RESET;
  std::cin >> command;
  return command;
}