#ifndef CONNECTION_CLOSED_EVENT_GUARD
#define CONNECTION_CLOSED_EVENT_GUARD

#include "event.h"
#include "events/connection_receiver.h"

namespace events
{
    class Connection_closed_event : public Event
    {
        public:
            Connection_closed_event ( events::Connection_receiver* identity ) :
                identity ( identity )
            {}

            std::string get_type () { return "Connection_closed_event"; }
            events::Connection_receiver* get_identity () const { return this->identity; }

            virtual ~Connection_closed_event () = default;

        private:
            events::Connection_receiver* identity;
    };
}

#endif //CONNECTION_CLOSED_EVENT_GUARD
