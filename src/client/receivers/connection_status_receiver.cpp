#include "connection_status_receiver.h"
#include "events/events.h"
#include "client/shared_data.h"

namespace client
{
    void Connection_status_receiver::receive ( std::shared_ptr < events::Event > event )
    {
        if ( event->get_type () == "Connection_closed_event" )
        {
            Shared_data::set_connected ( false );
        }
        else if ( event->get_type () == "Connection_established_event" )
        {
            Shared_data::set_connected ( true );
        }
    }
}
