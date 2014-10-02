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
                if ( method == "file" )
                {
                    content = json.get_string ( "content" );
                    file_name = json.get_string ( "file_name" );
                }
            }

            std::string get_type () { return "Add_torrent_event"; }
            std::string get_url () const { return this->url; }
            std::string get_method () const { return method; }
            std::string get_content () const { return content; }
            std::string get_file_name () const { return file_name; }

            virtual ~Add_torrent_event () noexcept = default;

        private:
            std::string url;
            std::string method;
            std::string content;
            std::string file_name;
    };
}

#endif //ADD_TORRENT_EVENT_GUARD
