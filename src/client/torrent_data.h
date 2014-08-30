#ifndef TORRENT_DATA_GUARD
#define TORRENT_DATA_GUARD

#include "utils/json_element.h"
#include "utils/json_list_element.h"

#include <memory>
#include <string>

namespace client
{
    class Torrent_data
    {
        public:
            Torrent_data () = default;
            Torrent_data ( std::string json );

            bool get_bool ( std::string identifier ) const;
            int get_int ( std::string identifier ) const;
            std::string get_string ( std::string identifier ) const;
            double get_double ( std::string identifier ) const;
            size_t get_size_t ( std::string identifier ) const;
            std::shared_ptr < utils::Json_element > get_element ( std::string identifier ) const;
            std::shared_ptr < utils::Json_list_element > get_list_element ( std::string identifier ) const;

            std::string get_truncated_double ( std::string identifier, int decimals ) const;
            std::string get_percentage ( std::string identifier, int decimals = 2 ) const;
            std::string get_transfer_speed ( std::string identifier, int decimals = 1 ) const;
            std::string get_file_size ( std::string identifier, int decimals = 1 ) const;
            std::string get_eta ( int numbers = 2 ) const;
            bool is_active () const;

            virtual ~Torrent_data () = default;

        private:
            std::string truncate_double ( double d, int decimals ) const;

            utils::Json_element json_data;
    };
}

#endif //TORRENT_DATA_GUARD
