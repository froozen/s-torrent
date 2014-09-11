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
                method ( json.get_string ( "method" ) )
            {
                if ( method == "url" )
                    url = json.get_string ( "url" );
            }

            std::string get_type () { return "Add_torrent_event"; }
            std::string get_url () const { return this->url; }
            std::string get_method () const { return method; }

            virtual ~Add_torrent_event () noexcept = default;

        private:
            std::string url;
            std::string method;
    };
}

#endif //ADD_TORRENT_EVENT_GUARD
