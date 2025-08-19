#ifndef COMMANDS_HEADERS
#define COMMANDS_HEADERS

namespace COMMANDS 
{
    class Command
    {
        public:
            int create_file(const char *path);
            int read_file(const char *path);
            int remove_file(const char *path);
    };
}

#endif 