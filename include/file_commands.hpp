#ifndef FILE_COMMANDS_HEADERS
#define FILE_COMMANDS_HEADERS

namespace FILE_COMMANDS 
{
    class File_commands
    {
        public:
            int create_file(const char *path);
            int read_file(const char *path);
            int write_file(const char *path, const char *text);
            int remove_file(const char *path);
            int move_file(const char *path_one, const char *path_two);
            int rename_file(const char *path_one, const char *path_two);
    };
}

#endif 