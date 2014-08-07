#ifndef SERVERSOCKET_GUARD
#define SERVERSOCKET_GUARD

#include <boost/asio.hpp>
#include <string>
#include <memory>

#include "client_socket.h"

namespace sockets
{
    class Server_socket
    {
        public:
            Server_socket ( int port );

            Client_socket accept ();

            virtual ~Server_socket () = default;

        private:
            std::shared_ptr < boost::asio::io_service > io_service;
            boost::asio::ip::tcp::acceptor acceptor;
    };
}

#endif //SERVERSOCKET_GUARD
