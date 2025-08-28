#include "../include/utilities.hpp"
#include <iostream>
#include <string>

using namespace UTILITIES_COMMANDS;

int Utilities_commands::print_text(std::string text) 
{
    std::cout << text << '\n';
    return 0;
}