#ifndef CONNECTION_ESTABLISHED_EVENT_GUARD
#define CONNECTION_ESTABLISHED_EVENT_GUARD

#include "events/event_types/event.h"
#include "events/connection_receiver.h"

#include <string>

namespace events
{
    class Connection_established_event : public events::Event
    {
        public:
            Connection_established_event ( events::Connection_receiver* origin ) :
                origin ( origin )
            {}

            std::string get_type () { return "Connection_established_event"; }
            events::Connection_receiver* get_origin () const { return origin; }

            virtual ~Connection_established_event () noexcept = default;

        private:
            events::Connection_receiver* origin;
    };
}

#endif //CONNECTION_ESTABLISHED_EVENT_GUARD
