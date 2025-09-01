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
    // checking file if it exist and also if it is readable
    if (access(path, F_OK) == -1 || access(path, R_OK) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // creating file descriptor for opening file to read it later
    int fd;
    fd = open(path, O_RDONLY);
    if (fd == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    ssize_t buffer_read;
    char buffer[64];

    // test code
    int count = 1;

    while ((buffer_read = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        std::cout << count << "-> ";
        std::cout << buffer << '\n';
        count++; 
    }

    if (buffer_read == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        if (close(fd) == -1) 
        {
            std::cerr << "-> Error occured, " << strerror(errno) << '\n';
            return 1;   
        }
        return 1;
    }

    if (close(fd) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;   
    }
    
    return 0;
}