#ifndef DIRECTORY_COMMANDS_HEADERS
#define DIRECTORY_COMMANDS_HEADERS

namespace DIRECTORY_COMMANDS
{
    class Directory_commands 
    {
        public:
            int create_directory(const char *path);
            int read_directory(const char *path);
            int get_current_directory();
            int remove_directory(const char *path);
    };
}

#endif
