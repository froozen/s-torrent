#ifndef DATA_FORMATTING_GUARD
#define DATA_FORMATTING_GUARD

#include <string>

namespace client
{
    std::string truncate_double ( double d, int decimals );
    std::string to_percentage ( double d, int decimals = 2 );
    std::string to_transfer_speed ( double d, int decimals = 1 );
    std::string to_file_size ( double d, int decimals = 1 );
}

#endif //DATA_FORMATTING_GUARD
