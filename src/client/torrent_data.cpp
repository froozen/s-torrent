#include "torrent_data.h"

#include <cmath>
#include <iostream>

#include "data_formatting.h"

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

        std::string Torrent_data::get_eta ( int numbers ) const
        {
            double wanted_not_done = get_double ( "total_wanted" ) - get_double ( "total_wanted_done" );
            int eta = wanted_not_done / get_int ( "download_payload_rate" );
            return client::to_duration ( eta );
        }

        std::string Torrent_data::get_ratio ( int decimals ) const
        {
            return client::truncate_double ( get_double ( "total_upload" ) / get_double ( "total_download" ), decimals );
        }

        bool Torrent_data::is_active () const
        {
        return get_int ( "download_payload_rate" ) > 0
            || get_int ( "updload_payload_rate" ) > 0
            || get_double ( "progress" ) < 1
            ;
        }
}
