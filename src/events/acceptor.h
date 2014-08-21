#ifndef ACCEPTORS_GUARD
#define ACCEPTORS_GUARD

#include "wrappers/asio/server_socket.h"

#include <string>
#include <thread>
#include <memory>

namespace events
{
    class Acceptor
    {
        public:
            Acceptor ( int port, std::string service );

            virtual ~Acceptor () = default;

        private:
            void do_accept ();

            int port;
            std::string service;
            std::shared_ptr < sockets::Server_socket > socket;
            std::thread do_accept_thread;
    };
}

#endif //ACCEPTORS_GUARD
