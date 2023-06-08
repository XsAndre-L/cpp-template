#pragma once

#include <string>
#include <iostream>

#define EXIT true
#define CONTINUE false

// ------------------ COLORS ------------------
// colors can be defined as:
// print("Hello World!", RED);
// or
// print(red("Hello ") + green("World!"));
// red("Hello ") + green("World!") -> gets eveluated to a multi color string

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

std::string red(const std::string &str);
std::string green(const std::string &str);
std::string yellow(const std::string &str);
std::string blue(const std::string &str);
std::string cyan(const std::string &str);

//----------------------------------------------

void fetchCommand(std::string &command);

void print(const std::string &str = "", const std::string &COLOR = RESET);
void println(const std::string &str = "", const std::string &COLOR = RESET);

std::string toLowerCase(const std::string &str);
