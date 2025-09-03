#ifndef UTILITIES_HEADERS
#define UTILITIES_HEADERS

#include <string>

namespace UTILITIES_COMMANDS
{
    class Utilities_commands 
    {
        public:
            int print_text(std::string text);
            int matching_pattern(std::string line, std::string pattern);
            int find_pattern(std::string pattern, const char *path);
            int count_details(const char *path);
    };
}

#endif
