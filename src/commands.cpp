#include "../include/commands.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace COMMANDS;

int Command::create_file(const char *path) 
{
    // checking if file already exists, if so then will generate error and return from here.
    if (access(path, F_OK) == 0) 
    {
        std::cout << "-> Error occured, file already exists\n";
        return 1; 
    }

    // creat() is old way to create file, now open() is used, because it give more control so will use that.
    // for now i am keeping 0644 permission, if needed then change this, or keep this as it is. 
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    if (close(fd) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    std::cout << "-> File created successfully" << '\n';
    return 0;
}

int Command::read_file(const char *path) 
{
    if (access(path, F_OK) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    int fd;
    fd = open(path, O_RDONLY);
    if (fd == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // for now i am keeping reading access seperatly if needed then merge it with above access one.
    if (access(path, R_OK) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }    

    ssize_t byte_read;

    // i need to see if i need to increase or decrease buffer.
    char buffer[128];
    while((byte_read = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        // for now i am using this way if needed then change to write or something else.
        std::cout << buffer << '\n';
    }

    if (byte_read == -1) 
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

// int Command::write_file(const char *path, std::string text) 
// {

// }

int Command::remove_file(const char *path) 
{
    // checking if the file we want to remove if exists in the first plave
    if (access(path, F_OK) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // using general one remove() instead of specific unlink() here, change it if you want.
    if (remove(path) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    std::cout << "-> File removed successfully\n";
    return 0; 
}