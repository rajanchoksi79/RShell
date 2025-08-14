#include "../include/commands.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace COMMANDS;

int Command::read_file(const char *path) 
{
    if (access(path, F_OK) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << std::endl;
        return 1;
    }

    int fd;
    fd = open(path, O_RDONLY);
    if (fd == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << std::endl;
        if (close(fd) == -1) 
        {
            std::cerr << "-> Error occured, " << strerror(errno) << std::endl;
            return 1;   
        }
        return 1;
    }

    // for now i am keeping reading access seperatly if needed then merge it with above access one.
    if (access(path, R_OK) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << std::endl;
        return 1;
    }    

    ssize_t byte_read;

    // i need to see if i need to increase or decrease buffer.
    char buffer[128];
    while((byte_read = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        // for now i am using this way if needed then change to write or something else.
        std::cout << buffer << std::endl;
    }

    if (byte_read == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << std::endl;
        if (close(fd) == -1) 
        {
            std::cerr << "-> Error occured, " << strerror(errno) << std::endl;
            return 1;   
        }
        return 1;
    }

    if (close(fd) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << std::endl;
        return 1;
    }

    return 0;
}