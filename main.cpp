#include <iostream>
#include <string>

int main() 
{
    while (true) 
    {   
        std::cout << "R:-> ";
        std::string user_input;
        std::getline(std::cin, user_input);

        if (user_input == "quit" || user_input == "exit") 
        {
            break;
        }
        else 
        {
            std::cout << "User Input: " << user_input << std::endl;
        }
    }

    return 0;
}