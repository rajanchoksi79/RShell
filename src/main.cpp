#include <iostream>
#include <string>
#include <typeinfo>
#include "../include/arg_parsing.hpp"
#include "../include/color.hpp"
using namespace ARGS;
using namespace Color_namespace;

int main() 
{
    while (true) 
    {   
        Arg_Parse arg_ins;

        // for now i am keeping cyan color if you want then change it
        std::cout << Color::bold_cyan << "\nRShell:~> " << Color::reset;
        std::string user_input;
        std::getline(std::cin >> std::ws, user_input);

        // for now i am adding one line before any output ok. 
        std::cout << std::endl;
        if (user_input == "quit" || user_input == "exit") 
        {
            break;
        }
        else 
        {
            arg_ins.arg_parsing(user_input);
        }
    }

    return 0;
}