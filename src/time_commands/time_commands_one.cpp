#include "../include/time_commands.hpp"
#include <iostream>
#include <string.h>
#include <sys/time.h>

using namespace DATETIME_COMMANDS;

int Datetime_commands::get_time() 
{   
    // created time_value struct instance to hold time value 
    struct timeval *time_value;
    
    // using gettimeofday to get time in time_value instance, return error if there is any, and passing NULL to second argument for now because this time zone thing in second arg is obsolate now.
    if (gettimeofday(time_value, NULL) == -1) 
    {
        std::cerr << "-> Error occured, " << strerror(errno) << '\n';
        return 1;
    }

    // on success displaying time data.
    std::cout << "-> " << time_value->tv_sec << '\n';
    return 0;
}