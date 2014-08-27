#define BOOST_ASIO_DYN_LINK

#include "torrent_data_to_json.h"

namespace torrent
{
    utils::Json_element to_json ( const libtorrent::torrent_handle& handle )
    {
        utils::Json_element json;
        json.set_string ( "name", handle.name () );
        json.set_string ( "save_path", handle.save_path () );

        libtorrent::torrent_status status = handle.status ();

        json.set_string ( "error", status.error );
        json.set_string ( "current_tracker", status.current_tracker );
        json.set_size_t ( "total_download", status.total_download );
        json.set_size_t ( "total_upload", status.total_upload );
        json.set_size_t ( "total_payload_download", status.total_payload_download );
        json.set_size_t ( "total_payload_upload", status.total_payload_upload );
        json.set_size_t ( "total_done", status.total_done );
        json.set_size_t ( "total_wanted_done", status.total_wanted_done );
        json.set_size_t ( "total_wanted", status.total_wanted );
        json.set_size_t ( "all_time_download", status.all_time_download );
        json.set_size_t ( "all_time_upload", status.all_time_upload );
        json.set_double ( "progress", status.progress );
        json.set_int ( "queue_position", status.queue_position );
        json.set_int ( "download_rate", status.download_rate );
        json.set_int ( "upload_rate", status.upload_rate );
        json.set_int ( "download_payload_rate", status.download_payload_rate );
        json.set_int ( "upload_payload_rate", status.upload_payload_rate );
        json.set_int ( "num_seeds", status.num_seeds );
        json.set_int ( "num_peers", status.num_peers );
        json.set_int ( "num_complete", status.num_complete );
        json.set_int ( "num_incomplete", status.num_incomplete );
        json.set_bool ( "paused", status.paused );

        return json;
    }
}
