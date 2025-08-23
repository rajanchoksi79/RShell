#include "../include/file_commands.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace FILE_COMMANDS;

int File_commands::copy_file(const char *path_one, const char *path_two) 
{
    
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