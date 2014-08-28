#include "event_system.h"

#include "events/hub.h"
#include "receivers/event_converter.h"
#include "receivers/add_torrent_receiver.h"
#include "receivers/torrent_data_requested_receiver.h"

#include <memory>

namespace torrent
{
    void Event_system::initialize ()
    {
        auto event_converter = std::make_shared < Event_converter > ();
        events::Hub::get_filter ( "Read_line_event" ).subscribe ( event_converter );

        auto add_torrent_receiver = std::make_shared < Add_torrent_receiver > ();
        events::Hub::get_filter ( "Add_torrent_event" ).subscribe ( add_torrent_receiver );

        auto torrent_data_requested_receiver = std::make_shared < Torrent_data_requested_receiver > ();
        events::Hub::get_filter ( "Torrent_data_requested_event" ).subscribe ( torrent_data_requested_receiver );
    }
}
