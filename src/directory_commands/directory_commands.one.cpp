#include "../include/directory_commands.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace DIRECTORY_COMMANDS;

int Directory_commands::create_directory(const char *path) 
{
    // checking if the given directory exist or not
    if (access(path, F_OK) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // creating directory and returning error in case of error
    if (mkdir(path, 0755) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;        
    }

    // returning success message in case of success
    std::cout << "-> New directory created successfully" << std::endl;
    return 0;
}

