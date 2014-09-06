#include "event_system.h"

#include "events/hub.h"
#include "receivers/event_converter.h"
#include "receivers/torrent_data_received_receiver.h"

#include <memory>

namespace client
{
    // Setup code for the event system, because I don't want to clutter the main to much
    void Event_system::initialize ()
    {
        auto event_converter = std::make_shared < Event_converter > ();
        events::Hub::get_filter ( "Read_line_event" ).subscribe ( event_converter );

        auto torrent_data_received_receiver = std::make_shared < Torrent_data_received_receiver > ();
        events::Hub::get_filter ( "Torrent_data_received_event" ).subscribe ( torrent_data_received_receiver );
    }
}
