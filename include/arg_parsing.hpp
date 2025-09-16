#ifndef ARGS_HEADERS
#define ARGS_HEADERS
#include <string>
#include <vector>

namespace ARGS 
{
    class Arg_Parse
    {
        public:
            void arg_parsing(std::string user_input);
            int arg_handling(std::vector<std::string> argument_vector);
    };
}

#endif 