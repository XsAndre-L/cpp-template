// #include <iostream>

#include "util/util.h"
#include "commands/commands.hpp"

int main()
{
    // Main Loop runs program
    while (true)
    {
        // Get command from user
        std::string cmd = getCommand();

        // Check important functions
        if (cmd == "exit")
            break;

        if (cmd == "help")
        {
            help_cmd_func();
            continue;
        }

        // Find The Command
        exec_cmd(cmd);
    }

    // try
    // {
    //     // Your code here
    //     println("Hello World!");
    //     std::cin.get();
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << "Exception: " << e.what() << std::endl;
    //     return 1;
    // }
}
