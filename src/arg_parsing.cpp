#include "../include/arg_parsing.hpp"
#include "../include/file_commands.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
using namespace ARGS;
using namespace FILE_COMMANDS;

int Arg_Parse::arg_handling(std::vector<std::string> argument_vector)
{

    File_commands command_executor;

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
        else if (argument_vector[0] == "movef") 
        {
            command_executor.move_file(argument_vector[1].c_str(), argument_vector[2].c_str());
        }
        else if (argument_vector[0] == "renamef") 
        {
            command_executor.rename_file(argument_vector[1].c_str(), argument_vector[2].c_str());
        }
        else
        {
            std::cout << "No proper argument is provided\n";
        }
    }

    return 0;
}

void Arg_Parse::arg_parsing(std::string user_input)
{

    std::vector<std::string> argument_vector;
    std::string non_literal_argument = "";
    std::string literal_argument = "";
    bool in_quotes = false;

    for (int i = 0; i < user_input.size(); i++)
    {

        if (user_input[i] == '"')
        {
            // reversing boolean value to handle start and end of double quotes
            in_quotes = !in_quotes;

            // when in second time double quotes hit in quotes is false and then adding argument to vector, because we cover every literal
            if (!in_quotes)
            {
                argument_vector.push_back(literal_argument);
            }
        }

        // while in quotes is true adding all the literal inside it in literal arguments
        else if (in_quotes)
        {
            literal_argument += user_input[i];
        }

        else if (!in_quotes)
        {
            if (user_input[i] != ' ')
            {
                non_literal_argument += user_input[i];
            }

            // adding argument when we find space, and then re assigning empty value to it to add another value later on.
            if (user_input[i] == ' ')
            {
                if (non_literal_argument != "")
                {
                    argument_vector.push_back(non_literal_argument);
                    non_literal_argument = "";
                }
            }
        }
    }

    // adding last argument, because it isn't added above with ' ' thing, and as for literal it covered in second double quote so it is not case with liteal arguments
    if (non_literal_argument != "")
    {
        argument_vector.push_back(non_literal_argument);
        non_literal_argument = "";
    }

    // handling arguments with the function
    arg_handling(argument_vector);

}