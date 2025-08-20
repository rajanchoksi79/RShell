#ifndef COMMANDS_HEADERS
#define COMMANDS_HEADERS

namespace COMMANDS 
{
    class Command
    {
        public:
            int create_file(const char *path);
            int read_file(const char *path);
            int write_file(const char *path, const char *text);
            int remove_file(const char *path);
    };
}

#endif 