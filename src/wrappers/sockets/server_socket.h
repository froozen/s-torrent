#ifndef SERVERSOCKET_GUARD
#define SERVERSOCKET_GUARD

#include <string>
#include <memory>

#include "client_socket.h"

namespace sockets
{
    class Server_socket
    {
        public:
            Server_socket ( int port );

            Client_socket next_socket ();
            void shutdown ();

            virtual ~Server_socket () = default;

        private:
            int socket_address;
            void error ( std::string message );
    };
}

#endif //SERVERSOCKET_GUARD
