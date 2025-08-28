#include "../include/utilities.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string>

using namespace UTILITIES_COMMANDS;

int Utilities_commands::print_text(std::string text) 
{
    std::cout << text << '\n';
    return 0;
}

int Utilities_commands::find_pattern(std::string pattern, const char *path) 
{
    if (access(path, F_OK) == -1 || access(path, R_OK) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    std::cout << "this command prints match patterns" << '\n';
    return 0;
}