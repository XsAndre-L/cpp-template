#include "util.h"

std::string getCommand()
{
  std::string command;
  std::cout << BLUE << "> " << RESET;
  std::cin >> command;
  return command;
}

void print(const std::string &str, const std::string &COLOR)
{
  std::cout << COLOR << str << RESET;
}

void println(const std::string &str, const std::string &COLOR)
{
  std::cout << COLOR << str << RESET << std::endl;
}
