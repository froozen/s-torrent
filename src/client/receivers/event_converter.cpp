#include "event_converter.h"

#include "events/hub.h"
#include "utils/json.h"
#include "client/events/events.h"
#include "events/events.h"

namespace client
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
                if ( type != "None" )
                {
                    if ( type == "Torrent_data_received_event" )
                        converted = std::make_shared < Torrent_data_received_event > ( json, read_line_event->get_origin () );
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
