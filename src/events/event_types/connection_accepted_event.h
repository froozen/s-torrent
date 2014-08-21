#ifndef CONNECTION_ACCEPTED_EVENT_GUARD
#define CONNECTION_ACCEPTED_EVENT_GUARD

#include "event.h"
#include "events/connection_receiver.h"

#include <string>

namespace events
{
    class Connection_accepted_event : public Event
    {
        public:
            Connection_accepted_event ( Connection_receiver* accepted, int port, std::string service ):
                accepted ( accepted ),
                port ( port ),
                service ( service )
            {}

            std::string get_type () { return "Connection_accepted_event"; }
            Connection_receiver* get_accepted () const { return this->accepted; }
            int get_port () const { return this->port; }
            std::string get_service () const { return this->service; }

            virtual ~Connection_accepted_event () = default;

        private:
            Connection_receiver* accepted;
            int port;
            std::string service;
    };
}

#endif //CONNECTION_ACCEPTED_EVENT_GUARD
