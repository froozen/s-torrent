#define BOOST_ASIO_DYN_LINK
#include "alert_event_creator.h"

#include "session.h"
#include "events/hub.h"
#include "events/events.h"

#include <libtorrent/alert.hpp>
#include <iostream>
#include <memory>

namespace torrent
{
    void Alert_event_creator::start ()
    {
        event_creator_thread = std::thread ( &Alert_event_creator::do_event_creation, this );
        event_creator_thread.detach ();
    }

    void Alert_event_creator::do_event_creation ()
    {
        while ( true )
        {
            std::shared_ptr < libtorrent::alert > received_alert = torrent::Session::pop_alert ();
            events::Hub::send ( std::make_shared < torrent::Alert_event > ( received_alert ) );
        }
    }
}
