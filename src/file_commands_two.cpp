#include "../include/file_commands.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace FILE_COMMANDS;

int File_commands::copy_file(const char *path_one, const char *path_two) 
{
    // checking both the path, if they exists or not, one by one, path one is with file and path two is just directory where we want to copy the file of path one 
    if (access(path_one, F_OK) == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    if (access(path_two, F_OK) == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    // opening file one with read only 
    int fd_one;
    fd_one = open(path_one, O_RDONLY);
    if (fd_one == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    // checking if file in path one has reading access 
    if (access(path_one, R_OK) == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    // creating file at file, where we copy content 
    int fd_two;
    fd_two = open(path_two, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_two == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    ssize_t byte_read, byte_write;
    char buffer[128];
    while ((byte_read = read(fd_one, buffer, sizeof(buffer))) > 0)
    {
        byte_write = write(fd_two, buffer, byte_read);
        if (byte_write == -1)
        {
            std::cerr << "-> Error occured " << strerror(errno) << '\n';
            if (close(fd_two) == -1)
            {
                std::cerr << "-> Error occured " << strerror(errno) << '\n';
                return 1;
            }
            // i need to know whether return can break the loop here because here i have to break the loop because of error, so i need to know that otherwise i have to use break;
            return 1;
        }
    }

    // closing both file after work done
    if (close(fd_one) == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    if (close(fd_two) == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    // displating message to user on successful copying of file
    std::cout << "-> Content copied from file one to file two successfully\n";
    return 0;

}

// for now i am implementing this way but i have to see, if there is other better way.
int File_commands::move_file(const char *path_one, const char *path_two)
{
    // checking if file exists or not with F_OK, if not then returning error
    if (access(path_one, F_OK) == -1)
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    if (path_one == path_two)
    {
        std::cout << "-> Error occured, both path address to same directory and file\n";
    }
    else
    {
        if (rename(path_one, path_two) == -1)
        {
            std::cerr << "-> Error occured, " << strerror(errno) << '\n';
            return 1;
        }
    }

    std::cout << "-> File moved successfully\n";
    return 0;
}

int File_commands::rename_file(const char *path_one, const char *path_two)
{
    // so if file exist or not with F_OK if not then retuning error
    if (access(path_one, F_OK) == -1)
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // renaming file with rename and returning error if there is error
    if (rename(path_one, path_two) == -1)
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // if all goes successful then informing user and returning success
    std::cout << "-> File renamed successfully!\n";
    return 0;
}