#include "../include/arg_parsing.hpp"
#include "../include/commands.hpp"
#include <iostream>
#include <string.h>
using namespace ARGS;
using namespace COMMANDS;

void Arg_Parse::arg_parsing(int argc, char argv[]) 
{
    // std::string flag ;
    // const char *path;
    // Command executor;

    // if (argc < 2) 
    // {
    //     std::cerr << "-> Error occured, " << strerror(errno) << std::endl;
    // }
    // else if (argc < 3) 
    // {
    //     flag = argv[1];
    //     path = argv[2];

    //     if (flag == "--readf") 
    //     {
    //         executor.read_file(path);
    //     }
    // }

    std::cout << "this is arg_parsing function" << std::endl;
}
