#include <iostream>

#include "util.h"

void println(const std::string &str)
{
    std::cout << GREEN << str << RESET << std::endl;
}

int main()
{
    while (true)
    {
        std::string command = getCommand();

        if (command == "exit")
            break;

        println(command);
    }

    try
    {
        // Your code here
        println("Hello World!");
        std::cin.get();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}
