#include "../include/file_commands.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace FILE_COMMANDS;

int File_commands::create_file(const char *path) 
{
    // checking if file already exists, if so then will generate error and return from here.
    if (access(path, F_OK) == 0) 
    {
        std::cout << "~> Error occured, file already exists\n";
        return 1; 
    }

    // creat() is old way to create file, now open() is used, because it give more control so will use that.
    // for now i am keeping 0644 permission, if needed then change this, or keep this as it is. 
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    if (close(fd) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    std::cout << "~> File created successfully, " << '\n';
    return 0;
}

int File_commands::read_file(const char *path) 
{
    if (access(path, F_OK) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    int fd;
    fd = open(path, O_RDONLY);
    if (fd == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // for now i am keeping reading access seperatly if needed then merge it with above access one.
    if (access(path, R_OK) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
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
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        if (close(fd) == -1) 
        {
            std::cerr << "~> Error occured, " << strerror(errno) << '\n';
            return 1;   
        }
        return 1;
    }

    if (close(fd) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    return 0;
}

int File_commands::write_file(const char *path, const char *text) 
{
    // checking if the file in which we want to write exists or not
    if (access(path, F_OK) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // opened file with write only, because i am writing in this file and also with append, so in non empty file, it append the given text at the end.
    int fd = open(path, O_WRONLY | O_APPEND);
    if (fd == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    ssize_t text_length {strlen(text)};
    ssize_t total_bytes_written {0};

    while (total_bytes_written < text_length) 
    {
        ssize_t bytes_write = write(fd, text + total_bytes_written, text_length - total_bytes_written);
        
        if (bytes_write == -1) 
        {
            std::cerr << "~> Error occured, " << strerror(errno) << '\n';
            if (close(fd) == -1) 
            {
                std::cerr << "~> Error occured, " << strerror(errno) << '\n';
                return 1;
            }
            return 1;
        }

        total_bytes_written += bytes_write;
    }     

    if (close(fd) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    std::cout << "~> Given text written in file successfully\n";
    return 0;

}

int File_commands::remove_file(const char *path) 
{
    // checking if the file we want to remove if exists in the first plave
    if (access(path, F_OK) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // using general one remove() instead of specific unlink() here, change it if you want.
    if (remove(path) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    std::cout << "~> File removed successfully\n";
    return 0; 
}
