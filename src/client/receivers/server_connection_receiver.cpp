#include "server_connection_receiver.h"

#include "events/events.h"
#include "client/events/events.h"
#include "events/hub.h"

#include <iostream>

namespace client
{
    Server_connection_receiver::Server_connection_receiver ( events::Connection_receiver* connection ) :
        connection ( connection )
    {}

    void Server_connection_receiver::receive ( std::shared_ptr < events::Event > event )
    {
        if ( event->get_type () == "Add_torrent_event" )
        {
            auto add_torrent_event = std::dynamic_pointer_cast < Add_torrent_event > ( event );
            events::Hub::send ( std::make_shared < events::Send_message_event > ( add_torrent_event->get_network_signal (), connection ) );
        }
    }
}
