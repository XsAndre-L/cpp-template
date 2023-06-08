// #include <iostream>

#include "util/util.hpp"
#include "commands/commands.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        // std::cout << "Number of arguments: " << argc << std::endl;
        std::cout << "Arguments: " << argv[1] << std::endl;
        // for (int i = 0; i < argc; ++i)
        // {
        //     std::cout << "Argument " << i << ": " << argv[i] << std::endl;
        // }
        return 0;
    }

    // Main Loop runs program
    while (true)
    {
        // Get command from user
        std::string cmd = getCommand();

        // Find The Command and execute it
        if (exec_cmd(cmd) == EXIT)
            break;

        println();
    }

    return 0;
}
