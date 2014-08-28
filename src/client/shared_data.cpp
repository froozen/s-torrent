#include "shared_data.h"

namespace client
{
    std::shared_ptr < std::vector < std::shared_ptr < utils::Json_element > > > Shared_data::torrent_data;
    std::mutex Shared_data::torrent_data_mutex;

    void Shared_data::set_torrent_data ( std::shared_ptr < std::vector < std::shared_ptr < utils::Json_element > > > new_torrent_data )
    {
        std::unique_lock < std::mutex > ( torrent_data_mutex );
        torrent_data.swap ( new_torrent_data );
    }

    std::shared_ptr < std::vector < std::shared_ptr < utils::Json_element > > > Shared_data::get_torrent_data ()
    {
        std::unique_lock < std::mutex > ( torrent_data_mutex );
        return torrent_data;
    }
}
