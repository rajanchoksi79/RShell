#include "../include/time_commands.hpp"
#include "../include/color.hpp"
#include <iostream>
#include <string.h>
#include <sys/time.h>
#include <ctime>
#include <iomanip>

using namespace DATETIME_COMMANDS;
using namespace Color_namespace;

int Datetime_commands::get_time() 
{   
    // created time_value struct instance to hold time value 
    struct timeval time_value;
    
    // using gettimeofday to get time in time_value instance, return error if there is any, and passing NULL to second argument for now because this time zone thing in second arg is obsolate now.
    if (gettimeofday(&time_value, NULL) == -1) 
    {
        std::cerr << "~> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // converting time to displayable time format and in current time
    std::time_t now_time = time_value.tv_sec;
    std::tm local_time = *std::localtime(&now_time);

    // on success displaying time data and return success
    std::cout << Color::bold_yellow << "~> Current Time: " << Color::reset << std::put_time(&local_time, "%H:%M:%S") << '\n';
    return 0;
}