#ifndef TORRENT_DATA_RECEIVED_EVENT_GUARD
#define TORRENT_DATA_RECEIVED_EVENT_GUARD

#include "events/event_types/event.h"
#include "events/connection_receiver.h"
#include "utils/json_element.h"
#include "utils/json_list_element.h"

#include <string>

namespace client
{
    class Torrent_data_received_event : public events::Event
    {
        public:
            Torrent_data_received_event ( const utils::Json_element& json, events::Connection_receiver* origin) :
                torrent_data_string ( json.get_list_element ( "torrent_data" )->to_small_string () ),
                origin ( origin )
            {}

            std::string get_type () { return "Torrent_data_received_event"; }
            std::string get_torrent_data_string () const { return torrent_data_string; }
            events::Connection_receiver* get_origin () const { return origin; }

            virtual ~Torrent_data_received_event () = default;

        private:
            std::string torrent_data_string;
            events::Connection_receiver* origin;
    };
}

#endif //TORRENT_DATA_RECEIVED_EVENT_GUARD
