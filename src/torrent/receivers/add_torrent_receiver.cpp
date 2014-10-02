#define BOOST_ASIO_DYN_LINK

#include "add_torrent_receiver.h"

#include "torrent/session.h"
#include "torrent/state.h"
#include "utils/json.h"
#include "utils/configuration.h"
#include "utils/base64.h"

#include <fstream>

namespace torrent
{
    void Add_torrent_receiver::receive ( std::shared_ptr < events::Event > event )
    {
        if ( event->get_type () == "Add_torrent_event" )
        {
            auto add_torrent_event = std::dynamic_pointer_cast < Add_torrent_event > ( event );
            libtorrent::add_torrent_params p;
            if ( add_torrent_event->get_method () == "url" )
                p.url = add_torrent_event->get_url ();

            else if ( add_torrent_event->get_method () == "file" )
            {
                std::string content = add_torrent_event->get_content ();
                content = utils::base64_decode ( content );

                std::ofstream torrent_file ( add_torrent_event->get_file_name () );
                torrent_file << content;
                torrent_file.close ();

                p.ti = new libtorrent::torrent_info ( add_torrent_event->get_file_name ().c_str () );
            }

            if ( ( p.save_path = utils::Configuration::get_root ()->get_string ( "save_path" ) ) == "None" )
                p.save_path = "./";

            libtorrent::torrent_handle added = Session::add_torrent ( p );
            added.set_download_limit ( utils::Configuration::get_root ()->get_int ( "download_limit" ) );

            utils::Json_element torrent_state;
            torrent_state.set_string ( "save_path", "./" );

            if ( add_torrent_event->get_method () == "url" )
            {
                torrent_state.set_string ( "method", "url" );
                torrent_state.set_string ( "url", add_torrent_event->get_url () );
            }
            else if ( add_torrent_event->get_method () == "file" )
            {
                torrent_state.set_string ( "method", "file" );
                torrent_state.set_string ( "file_name", add_torrent_event->get_file_name () );
            }

            State::add_torrent_state ( torrent_state );
        }
    }
}
