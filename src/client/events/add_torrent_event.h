#ifndef ADD_TORRENT_EVENT_GUARD
#define ADD_TORRENT_EVENT_GUARD

#include "events/event_types/event.h"
#include <string>

namespace client
{
    class Add_torrent_event : public events::Event
    {
        public:
            enum class Method
            {
                URL,
                FILE
            };

            Add_torrent_event ( Method method, std::string source );

            std::string get_type () { return "Add_torrent_event"; }
            std::string get_source () const { return source; }
            Method get_method () const { return method; }

            std::string get_network_signal ();

            virtual ~Add_torrent_event () noexcept = default;

        private:
            Method method;
            std::string source;
    };
}

#endif //ADD_TORRENT_EVENT_GUARD
