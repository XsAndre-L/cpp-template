#pragma once

#include <string>
#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

std::string getCommand();

void fetchCommand(std::string &command);

void print(const std::string &str = "", const std::string &COLOR = RESET);
void println(const std::string &str = "", const std::string &COLOR = RESET);