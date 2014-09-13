#ifndef SERVER_CONNECTION_GUARD
#define SERVER_CONNECTION_GUARD

#include "events/connection_receiver.h"
#include "events/receiver.h"
#include "events/event_types/event.h"

#include <memory>

namespace client
{
    class Server_connection_receiver : public events::Receiver < std::shared_ptr < events::Event > >
    {
        public:
            Server_connection_receiver ( events::Connection_receiver* connection );

            void receive ( std::shared_ptr < events::Event > event );

            virtual ~Server_connection_receiver () = default;

        private:
            events::Connection_receiver* connection;
    };
}

#endif //SERVER_CONNECTION_GUARD
