#define BOOST_ASIO_DYN_LINK

#include "torrent_data_to_json.h"

namespace torrent
{
    // Turn a libtorrent::torrent_handle into a Json_element
    utils::Json_element to_json ( const libtorrent::torrent_handle& handle )
    {
        utils::Json_element json;
        json.set_string ( "name", handle.name () );
        json.set_string ( "save_path", handle.save_path () );

        libtorrent::torrent_status status = handle.status ();

        json.set_string ( "error", status.error );
        json.set_string ( "current_tracker", status.current_tracker );
        json.set_double ( "total_download", status.total_download );
        json.set_double ( "total_upload", status.total_upload );
        json.set_double ( "total_payload_download", status.total_payload_download );
        json.set_double ( "total_payload_upload", status.total_payload_upload );
        json.set_double ( "total_done", status.total_done );
        json.set_double ( "total_wanted_done", status.total_wanted_done );
        json.set_double ( "total_wanted", status.total_wanted );
        json.set_double ( "all_time_download", status.all_time_download );
        json.set_double ( "all_time_upload", status.all_time_upload );
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

        if ( status.state == libtorrent::torrent_status::state_t::queued_for_checking )
            json.set_string ( "state", "queued_for_checking" );
        else if ( status.state == libtorrent::torrent_status::state_t::checking_files )
            json.set_string ( "state", "checking_files" );
        else if ( status.state == libtorrent::torrent_status::state_t::downloading_metadata )
            json.set_string ( "state", "downloading_metadata" );
        else if ( status.state == libtorrent::torrent_status::state_t::downloading )
            json.set_string ( "state", "downloading" );
        else if ( status.state == libtorrent::torrent_status::state_t::finished )
            json.set_string ( "state", "finished" );
        else if ( status.state == libtorrent::torrent_status::state_t::seeding )
            json.set_string ( "state", "seeding" );
        else if ( status.state == libtorrent::torrent_status::state_t::allocating )
            json.set_string ( "state", "allocating" );
        else if ( status.state == libtorrent::torrent_status::state_t::checking_resume_data )
            json.set_string ( "state", "checking_resume_data" );

        return json;
    }
}
