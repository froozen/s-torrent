#define BOOST_ASIO_DYN_LINK

#include "torrent_data_requested_receiver.h"

#include "events/hub.h"
#include "events/events.h"
#include "torrent/session.h"
#include "torrent/torrent_data_to_json.h"
#include "utils/json_element.h"
#include "utils/json_list_element.h"

#include <vector>
#include <libtorrent/torrent_handle.hpp>

namespace torrent
{
    void Torrent_data_requested_receiver::receive ( std::shared_ptr < events::Event > event )
    {
        if ( event->get_type () == "Torrent_data_requested_event" )
        {
            std::vector < libtorrent::torrent_handle > torrents = Session::get_torrents ();
            utils::Json_list_element json_torrents;
            for ( auto handle : torrents )
            {
                json_torrents.append_element ( to_json ( handle ) );
            }

            auto torrent_data_requested_event = std::dynamic_pointer_cast < Torrent_data_requested_event > ( event );
            utils::Json_element event_json;
            event_json.set_string ( "type", "Torrent_data_received_event" );
            event_json.set_list_element ( "torrent_data", json_torrents );
            auto send_message_event = std::make_shared < events::Send_message_event >
                ( event_json.to_small_string (), torrent_data_requested_event->get_origin () );
            events::Hub::send ( send_message_event );
        }
    }
}
