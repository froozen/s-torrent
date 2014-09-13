#ifndef CLIENT_EVENT_SYSTEM_GUARD
#define CLIENT_EVENT_SYSTEM_GUARD

#include "events/connection_receiver.h"

namespace client
{
    class Event_system
    {
        public:
            static void initialize ( events::Connection_receiver* connection );

        private:
            Event_system () = default;
    };
}

#endif //CLIENT_EVENT_SYSTEM_GUARD
