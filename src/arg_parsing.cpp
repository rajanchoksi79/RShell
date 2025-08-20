#include "../include/arg_parsing.hpp"
#include "../include/commands.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
using namespace ARGS;
using namespace COMMANDS;

int Arg_Parse::arg_parsing(std::string user_input) 
{
    std::vector<std::string> argument_vector;
    std::stringstream ss(user_input);
    std::string token;

    while(getline(ss, token, ' ')) {
        if (!token.empty()) {
            argument_vector.push_back(token);
        }
    }

    Command command_executor;

    if (argument_vector.size() < 2) 
    {
        std::cerr << "-> Error occured, Please enter valid flag to continue" << std::endl;
        return 1;
    }
    else 
    {
        if (argument_vector[0] == "createf") 
        {
            command_executor.create_file(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "readf") 
        {
            command_executor.read_file(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "removef") 
        {
            command_executor.remove_file(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "writef") 
        {
            command_executor.write_file(argument_vector[1].c_str(), argument_vector[2].c_str());
        }
    }

    return 0;
}
