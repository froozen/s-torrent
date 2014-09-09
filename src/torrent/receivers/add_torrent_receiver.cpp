#define BOOST_ASIO_DYN_LINK

#include "add_torrent_receiver.h"

#include "torrent/session.h"
#include "torrent/state.h"
#include "utils/json.h"

namespace torrent
{
    void Add_torrent_receiver::receive ( std::shared_ptr < events::Event > event )
    {
        if ( event->get_type () == "Add_torrent_event" )
        {
            auto add_torrent_event = std::dynamic_pointer_cast < Add_torrent_event > ( event );
            // A lot of these thins will later be replaced with Configuration values
            libtorrent::add_torrent_params p;
            p.url = add_torrent_event->get_url ();
            p.save_path = "./";
            libtorrent::torrent_handle added = Session::add_torrent ( p );
            added.set_download_limit ( 300000 );

            utils::Json_element torrent_state;
            torrent_state.set_string ( "url", add_torrent_event->get_url () );
            torrent_state.set_string ( "save_path", "./" );
            State::add_torrent_state ( torrent_state );
        }
    }
}
