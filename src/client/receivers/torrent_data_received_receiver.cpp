#include "torrent_data_received_receiver.h"

#include "utils/json_element.h"
#include "utils/json_list_element.h"
#include "client/shared_data.h"
#include "client/events/events.h"
#include "events/hub.h"
#include "events/events.h"

#include <vector>
#include <thread>
#include <chrono>

namespace client
{
    void Torrent_data_received_receiver::receive ( std::shared_ptr < events::Event > event )
    {
        if ( event->get_type () == "Torrent_data_received_event" )
        {
            auto torrent_data_received_event = std::dynamic_pointer_cast < Torrent_data_received_event > ( event );
            utils::Json_list_element torrent_data  ( torrent_data_received_event->get_torrent_data_string () );

            std::shared_ptr < std::vector < std::shared_ptr < utils::Json_element > > > new_torrent_data =
                std::make_shared < std::vector < std::shared_ptr < utils::Json_element > > > ();

            for ( int i = 0; i < torrent_data.size (); i++ )
                new_torrent_data->push_back ( torrent_data.get_element ( i ) );

            client::Shared_data::set_torrent_data ( new_torrent_data );

            utils::Json_element torrent_data_request;
            torrent_data_request.set_string ( "type", "Torrent_data_requested_event" );
            std::this_thread::sleep_for ( std::chrono::seconds ( 3 ) );
            events::Hub::send ( std::make_shared < events::Send_message_event >
                    ( torrent_data_request.to_small_string (), torrent_data_received_event->get_origin () ) );
        }
    }
}
