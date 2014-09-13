#ifndef CLIENT_INTERFACE_GUARD
#define CLIENT_INTERFACE_GUARD

#include "events/connection_receiver.h"

namespace client
{
    class Interface
    {
        public:
            static void run ( events::Connection_receiver* connection );
    };
}

#endif //CLIENT_INTERFACE_GUARD
