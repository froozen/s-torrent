#include "torrent_data.h"

#include <cmath>
#include <iostream>

namespace client
{
        Torrent_data::Torrent_data ( std::string json ) :
            json_data ( json )
        {}

        bool Torrent_data::get_bool ( std::string identifier ) const
        {
            return json_data.get_bool ( identifier );
        }

        int Torrent_data::get_int ( std::string identifier ) const
        {
            return json_data.get_int ( identifier );
        }

        std::string Torrent_data::get_string ( std::string identifier ) const
        {
            return json_data.get_string ( identifier );
        }

        double Torrent_data::get_double ( std::string identifier ) const
        {
            return json_data.get_double ( identifier );
        }

        size_t Torrent_data::get_size_t ( std::string identifier ) const
        {
            return json_data.get_size_t ( identifier );
        }

        std::shared_ptr < utils::Json_element > Torrent_data::get_element ( std::string identifier ) const
        {
            return json_data.get_element ( identifier );
        }

        std::shared_ptr < utils::Json_list_element > Torrent_data::get_list_element ( std::string identifier ) const
        {
            return json_data.get_list_element ( identifier );
        }

        std::string Torrent_data::truncate_double ( double d, int decimals ) const
        {
            int preceding;
            if ( d != 0 ) preceding = std::log10 ( d ) + 1;
            else preceding = 1;

            // std::cout << std::to_string ( d ) + " " + std::to_string ( preceding ) << std::endl;
            std::string truncated = std::to_string ( d );
            truncated = std::string ( truncated.begin (), truncated.begin () + preceding + 1 + decimals );

            return truncated;
        }

        std::string Torrent_data::get_truncated_double ( std::string identifier, int decimals ) const
        {
            double d = json_data.get_double ( identifier );
            return truncate_double ( d, decimals );
        }

        std::string Torrent_data::get_percentage ( std::string identifier, int decimals ) const
        {
            double d = json_data.get_double ( identifier ) * 100;
            return truncate_double ( d, decimals ) + "%";
        }

        std::string Torrent_data::get_transfer_speed ( std::string identifier, int decimals ) const
        {
            double speed = get_int ( identifier );
            if ( speed > 1000000000 )
                return truncate_double ( speed / 1000000000, decimals ) + " GiB/s";
            else if ( speed > 1000000 )
                return truncate_double ( speed / 1000000, decimals ) + " MiB/s";
            else if ( speed > 1000 )
                return truncate_double ( speed / 1000, decimals ) + " KiB/s";
            else
                return truncate_double ( speed, decimals ) + "   B/s";
        }

        std::string Torrent_data::get_file_size ( std::string identifier, int decimals ) const
        {
            double size = get_double ( identifier );
            if ( size > 1000000000 )
                return truncate_double ( size / 1000000000, decimals ) + " GB";
            else if ( size > 1000000 )
                return truncate_double ( size / 1000000, decimals ) + " MB";
            else if ( size > 1000 )
                return truncate_double ( size / 1000, decimals ) + " KB";
            else
                return truncate_double ( size, decimals ) + "  B";
        }

        std::string Torrent_data::get_eta ( int numbers ) const
        {
            double wanted_not_done = get_double ( "total_wanted" ) - get_double ( "total_wanted_done" );
            int eta = wanted_not_done / get_int ( "download_payload_rate" );
            std::string eta_string;

            // days
            if ( numbers > 0 )
            {
                int days = eta / ( 60 * 60 * 24 );
                if ( days > 0 )
                {
                    eta_string += std::to_string ( days ) + "d ";
                    numbers --;
                    eta -= days * 60 * 60 * 24;
                }
            }

            // hours
            if ( numbers > 0 )
            {
                int hours = eta / ( 60 * 60 );
                if ( hours > 0 )
                {
                    eta_string += std::to_string ( hours ) + "h ";
                    numbers --;
                    eta -= hours * 60 * 60;
                }
            }

            // minutes
            if ( numbers > 0 )
            {
                int minutes = eta / 60;
                if ( minutes > 0 )
                {
                    eta_string += std::to_string ( minutes ) + "m ";
                    numbers --;
                    eta -= minutes * 60;
                }
            }

            // seconds
            if ( numbers > 0 )
            {
                if ( eta > 0 || eta_string == "" )
                    eta_string += std::to_string ( eta ) + "s ";
            }

            return std::string ( eta_string.begin (), eta_string.end () - 1 );
        }

        bool Torrent_data::is_active () const
        {
        return get_int ( "download_payload_rate" ) > 0
            || get_int ( "updload_payload_rate" ) > 0
            || get_double ( "progress" ) < 1
            ;
        }
}
