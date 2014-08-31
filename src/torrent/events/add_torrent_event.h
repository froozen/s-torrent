#ifndef ADD_TORRENT_EVENT_GUARD
#define ADD_TORRENT_EVENT_GUARD

#include "events/events.h"
#include "utils/json.h"
#include "events/connection_receiver.h"

#include <string>

namespace torrent
{
    class Add_torrent_event : public events::Event
    {
        public:
            Add_torrent_event ( const utils::Json_element& json, events::Connection_receiver* origin ) :
                url ( json.get_string ( "url" ) )
            {}

            std::string get_type () { return "Add_torrent_event"; }
            std::string get_url () const { return this->url; }

            virtual ~Add_torrent_event () = default;

        private:
            std::string url;
    };
}

#endif //ADD_TORRENT_EVENT_GUARD
