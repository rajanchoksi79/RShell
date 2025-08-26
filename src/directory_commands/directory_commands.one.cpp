#include "../include/directory_commands.hpp"
#include "../include/color.hpp"
#define _DEFAULT_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
using namespace DIRECTORY_COMMANDS;
using namespace Color_namespace;

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
    std::cout << "-> New directory created successfully" << '\n';
    return 0;
}

// reading and printing content of directory
int read_directory(const char *path)
{
    if (access(path, F_OK) == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        std::cerr << "-> Error occured " << strerror(errno) << std::endl;
        if (closedir(dir) == -1)
        {
            std::cerr << "-> Error occured " << strerror(errno) << '\n';
            return 1;
        }
        return 1;
    }

    struct dirent *entry;
    struct stat file_detail;
    char full_path[PATH_MAX];
    
    int file_count = 0;
    int directory_count = 0; 

    // new line before printing any detail from below.
    std::cout << '\n';    
    // printf("\n");

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_detail) == 0)
        {
            if ((file_detail.st_mode & S_IFMT) == S_IFREG)
            {
                std::cout << "├── " << entry->d_name << '\n';
                file_count += 1;
            }
            else if ((file_detail.st_mode & S_IFMT) == S_IFDIR)
            {   
                std::cout << "├── " << Color::yellow << entry->d_name << Color::reset << '\n';
                directory_count += 1;
            }
            else if ((file_detail.st_mode & S_IFMT) == S_IFLNK)
            {
                std::cout << "├── " << Color::green << entry->d_name << Color::reset << '\n';
            }
            else
            {   
                std::cout << "├── " << entry->d_name << std::endl;
            }
        }
        else 
        {
            std::cerr << "-> Error occured " << strerror(errno) << '\n';
            return 1;
        }
    }

    std::cout << Color::bold_yellow << "\n-> " << directory_count << (directory_count == 1 ? " Directory, " : " Directories, "); 
    
    std::cout << Color::bold_yellow << file_count << (file_count == 1 ? " File" : " Files") << Color::reset << '\n';
    std::cout << '\n';

    if (closedir(dir) == -1)
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }
    return 0;
}