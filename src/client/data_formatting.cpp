#include "data_formatting.h"

#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace client
{
    // Limit a double to a certain number of decimals
    std::string truncate_double ( double d, int decimals )
    {
        std::stringstream precision_stream;
        std::string out_string;
        precision_stream << std::fixed << std::setprecision ( decimals ) << d;
        precision_stream >> out_string;

        return out_string;
    }

    // Create percentage from double
    std::string to_percentage ( double d, int decimals )
    {
        return truncate_double ( d * 100, decimals ) + "%";
    }

    // Create transfer speed from number of bytes
    std::string to_transfer_speed ( double speed, int decimals )
    {
        if ( speed > 1000000000 )
            return truncate_double ( speed / 1000000000, decimals ) + " GiB/s";
        else if ( speed > 1000000 )
            return truncate_double ( speed / 1000000, decimals ) + " MiB/s";
        else if ( speed > 1000 )
            return truncate_double ( speed / 1000, decimals ) + " KiB/s";
        else
            return truncate_double ( speed, decimals ) + "   B/s";
    }

    // Create file size from number of bytes
    std::string to_file_size ( double size, int decimals )
    {
        if ( size > 1000000000 )
            return truncate_double ( size / 1000000000, decimals ) + " GB";
        else if ( size > 1000000 )
            return truncate_double ( size / 1000000, decimals ) + " MB";
        else if ( size > 1000 ) return truncate_double ( size / 1000, decimals ) + " KB"; else return truncate_double ( size, decimals ) + "  B";
    }

    // Create duration from number of seconds
    std::string to_duration ( int seconds, int numbers )
    {
        if ( seconds == 0 )
            return "0s";

        std::string duration_string;
        std::vector < std::string > units = { "y", "w", "d", "h", "m", "s" };
        std::vector < int > step = { 52, 7, 24, 60, 60, 1 };

        for ( auto it = units.begin (); it != units.end (); it++ )
        {
            if ( numbers > 0 )
            {
                int distance = std::distance ( units.begin (), it );
                int steps = std::accumulate ( step.begin () + distance, step.end (), 1, [] ( int a, int b ) { return a * b; } );
                int amount = seconds / steps;
                if ( amount > 0 )
                {
                    duration_string += std::to_string ( amount ) + *it + " ";
                    numbers--;
                    seconds -= amount * steps;
                }
            }
        }

        return std::string ( duration_string.begin (), duration_string.end () - 1 );
    }
}
