#include "util.hpp"

std::string red(const std::string &str)
{
  return RED + str + RESET;
}
std::string green(const std::string &str)
{
  return GREEN + str + RESET;
}
std::string yellow(const std::string &str)
{
  return YELLOW + str + RESET;
}
std::string blue(const std::string &str)
{
  return BLUE + str + RESET;
}
std::string cyan(const std::string &str)
{
  return CYAN + str + RESET;
}

void print(const std::string &str, const std::string &COLOR)
{
  std::cout << COLOR << str << RESET;
}

void println(const std::string &str, const std::string &COLOR)
{
  std::cout << COLOR << str << RESET << std::endl;
}

std::string toLowerCase(const std::string &str)
{
  std::string result;
  for (char c : str)
  {
    result += std::tolower(c);
  }
  return result;
}