#ifndef CLIENT_SOCKET_GUARD
#define CLIENT_SOCKET_GUARD

#include <string>
#include <deque>
#include <memory>

namespace sockets
{
    class Client_socket
    {
        public:
            Client_socket ( std::string address, int port );
            Client_socket ( int socket_address );
            Client_socket ( Client_socket&& ) = default;

            // I don't want this to be copyable, because of boost not allowing it as well
            Client_socket& operator= ( Client_socket&& ) = default;
            Client_socket& operator= ( const Client_socket& ) = delete;

            std::string read_line ( std::string linebreak = {'\n'} ); // Read until '\n'
            void send ( std::string message, std::string linebreak = {'\n'} );
            void shutdown ();

            virtual ~Client_socket () = default;

        private:
            int socket_address;
            void error ( std::string message );
            std::string get_line ( std::string& from, const std::string& delimiter );
            bool ends_with ( const std::string& target, const std::string& ending );

            // Attributes for Client_socket::read_line
            std::deque < std::string > next_lines;
            std::string line_rest;
    };
}

#endif //CLIENT_SOCKET_GUARD
