#include "event_converter.h"

#include "events/hub.h"
#include "utils/json.h"
#include "torrent/events/events.h"

namespace torrent
{
    void Event_converter::receive ( std::shared_ptr < events::Event > event )
    {
        if ( event->get_type () == "Read_line_event" )
        {
            try
            {
                auto read_line_event = std::dynamic_pointer_cast < events::Read_line_event > ( event );
                utils::Json_element json ( read_line_event->get_line () );

                std::string type = json.get_string ( "type" );
                std::shared_ptr < events::Event > converted;
                // Convert the event appropriately
                if ( type != "None" )
                {
                    if ( type == "Add_torrent_event" )
                        converted = std::make_shared < Add_torrent_event > ( json, read_line_event->get_origin () );
                    else if ( type == "Torrent_data_requested_event" )
                        converted = std::make_shared < Torrent_data_requested_event > ( json, read_line_event->get_origin () );
                }

                if ( converted != nullptr )
                    events::Hub::send ( converted );
            }
            // JSON parsing might fail
            catch ( std::runtime_error& e )
            {}
        }
    }
}
