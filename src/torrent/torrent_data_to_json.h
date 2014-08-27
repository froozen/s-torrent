#ifndef TORRENT_DATA_TO_JSON_GUARD
#define TORRENT_DATA_TO_JSON_GUARD

#include <libtorrent/torrent_handle.hpp>

#include "utils/json_element.h"

namespace torrent
{
    utils::Json_element to_json ( const libtorrent::torrent_handle& handle );
}

#endif //TORRENT_DATA_TO_JSON_GUARD
