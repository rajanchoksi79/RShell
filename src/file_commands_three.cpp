#include "../include/file_commands.hpp"
#include "../include/color.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace FILE_COMMANDS;
using namespace Color_namespace;

// in fms i used stat(), but here i am using fstat(), with fd
int File_commands::file_info(const char *path) 
{
    // checking if the given file exist or not.
    if (access(path, F_OK) == -1) 
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1; 
    }

    // opening file, getting fd on success or in -1 in case error and retruning from method in that case.
    int fd = open(path, O_RDONLY, 0644);
    if (fd == -1) 
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        return 1;
    }

    // creating struct instance for holding file info
    struct stat file_details;

    // if -1 then returning error other wise going on.
    if (fstat(fd, &file_details) == -1) 
    {
        std::cerr << "-> Error occured " << strerror(errno) << '\n';
        
        // closing fd in case of error in fstat()
        if (close(fd) == -1) 
        {
            std::cerr << "-> Error occured " << strerror(errno) << '\n';
            return 1;
        }

        // returning error if there is error in fstat()
        return 1;
    }

    // displaying file information
    std::cout << Color::bold_yellow << "\n-> File info: \n" << Color::reset << '\n';

    std::cout << "File size: " << file_details.st_size << '\n';
    std::cout << "Owner UID: " << file_details.st_uid << '\n';
    std::cout << "Group UID: " << file_details.st_gid << '\n';
    std::cout << "Permissions: " << file_details.st_mode << '\n';
    
    return 0;
}