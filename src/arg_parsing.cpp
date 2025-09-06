#include "../include/arg_parsing.hpp"
#include "../include/file_commands.hpp"
#include "../include/directory_commands.hpp"
#include "../include/time_commands.hpp"
#include "../include/utilities.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
using namespace ARGS;
using namespace FILE_COMMANDS;
using namespace DIRECTORY_COMMANDS;
using namespace DATETIME_COMMANDS;
using namespace UTILITIES_COMMANDS;

int Arg_Parse::arg_handling(std::vector<std::string> argument_vector)
{

    // creating different instance to execute different types of commands
    File_commands file_command_executor;
    Directory_commands dir_command_executor;
    Datetime_commands datetime_executor;
    Utilities_commands utilities_executor;

    // handling arguments, returning error if there is any, else alloting and executing commands
    if (argument_vector.size() < 1)
    {
        std::cerr << "~> Error occured, Please enter valid flag to continue" << std::endl;
        return 1;
    }
    else
    {
        if (argument_vector[0] == "createf")
        {
            file_command_executor.create_file(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "readf")
        {
            file_command_executor.read_file(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "removef")
        {
            file_command_executor.remove_file(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "writef")
        {
            file_command_executor.write_file(argument_vector[1].c_str(), argument_vector[2].c_str());
        }
        else if (argument_vector[0] == "copyf")
        {
            file_command_executor.copy_file(argument_vector[1].c_str(), argument_vector[2].c_str());
        }
        else if (argument_vector[0] == "movef")
        {
            file_command_executor.move_file(argument_vector[1].c_str(), argument_vector[2].c_str());
        }
        else if (argument_vector[0] == "renamef")
        {
            file_command_executor.rename_file(argument_vector[1].c_str(), argument_vector[2].c_str());
        }
        else if (argument_vector[0] == "detailf")
        {
            file_command_executor.file_info(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "createdir")
        {
            dir_command_executor.create_directory(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "readdir") 
        {
            dir_command_executor.read_directory(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "getdir") 
        {
            dir_command_executor.get_current_directory();
        }
        else if (argument_vector[0] == "removedir") 
        {
            dir_command_executor.remove_directory(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "time") 
        {
            datetime_executor.get_time();
        }
        else if (argument_vector[0] == "print") 
        {
            utilities_executor.print_text(argument_vector[1]);
        }
        else if (argument_vector[0] == "pattern") 
        {
            utilities_executor.find_pattern(argument_vector[1], argument_vector[2].c_str());
        } 
        else if (argument_vector[0] == "count") 
        {
            utilities_executor.count_details(argument_vector[1].c_str());
        }
        else if (argument_vector[0] == "processid") 
        {
            utilities_executor.get_process_id();
        }
        else if (argument_vector[0] == "pprocessid") 
        {
            utilities_executor.get_parents_process_id();
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