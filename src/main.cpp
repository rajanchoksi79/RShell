#include <iostream>
#include <string>
#include "../include/arg_parsing.hpp"
#include "../include/color.hpp"
using namespace ARGS;
using namespace Color_namespace;

int main() 
{
    while (true) 
    {   
        Arg_Parse arg_ins;
        Color color;

        // for now i am keeping cyan color if you want then change it
        std::cout << color.cyan << "\n R:--> " << color.reset;
        std::string user_input;
        std::getline(std::cin, user_input);

        // for now i am adding one line before any output ok. 
        std::cout << std::endl;
        if (user_input == "quit" || user_input == "exit") 
        {
            break;
        }
        else 
        {
            arg_ins.arg_parsing();
            std::cout << "User Input: " << user_input << std::endl;
        }
    }

    return 0;
}