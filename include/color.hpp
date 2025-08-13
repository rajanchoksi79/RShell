#ifndef COLOR_HEADERS
#define COLOR_HEADERS

#include <string>

namespace Color_namespace 
{
    class Color {
        public:
            static inline const std::string reset   = "\033[0m";
            static inline const std::string black   = "\033[30m";
            static inline const std::string red     = "\033[31m";
            static inline const std::string green   = "\033[32m";
            static inline const std::string yellow  = "\033[33m";
            static inline const std::string blue    = "\033[34m";
            static inline const std::string magenta = "\033[35m";
            static inline const std::string cyan    = "\033[36m";
            static inline const std::string white   = "\033[37m";

            // Bold variants
            static inline const std::string bold_red     = "\033[1;31m";
            static inline const std::string bold_green   = "\033[1;32m";
            static inline const std::string bold_yellow  = "\033[1;33m";
            static inline const std::string bold_blue    = "\033[1;34m";
    };
}

#endif
