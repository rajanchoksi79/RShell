#include "../include/utilities.hpp"
#include "../include/color.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string>
#include <vector>

using namespace UTILITIES_COMMANDS;
using namespace Color_namespace;


int Utilities_commands::print_text(std::string text)
{
    std::cout << text << '\n';
    return 0;
}

// now i am making this global variable so that i can use in two methods
int count = 0;

// this method is for matching pattern with sub string of each line, that i will use in find pattern method.
int Utilities_commands::matching_pattern(std::string line, std::string pattern) 
{
   // for now i am doing split thing manually, later if you like you can add method or library thing.
   std::vector<std::string> line_array;
   std::string word; 

   for (int i = 0; i < line.size(); i++) 
   {
        if(line[i] == ' ') 
        {
            line_array.push_back(word);
            word.clear();
        } 
        else 
        {
            word.push_back(line[i]);
        }
   } 

   // matching pattern with each element of line
   for (int j = 0; j < line_array.size(); j++) 
   {
        if (pattern == line_array[j]) 
        {
            std::cout << Color::bold_yellow <<"Line: " << count << " -> " << Color::reset << '\t' << line << '\n';
            return 0;
        }
   }

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
    // for now i am keeping buffer upto 1024 chars, but if needed then set it to max value thing.
    char buffer[1024];
    std::string line;

    while ((buffer_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < buffer_read; i++) 
        {
            if (buffer[i] == '\n') 
            {
                count++;
                Utilities_commands::matching_pattern(line, pattern);
                line.clear();
            }
            else 
            {
                line.push_back(buffer[i]);
            }
        }
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