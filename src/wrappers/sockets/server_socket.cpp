#include "server_socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include <stdexcept>

namespace sockets
{
    Server_socket::Server_socket ( int port )
    {
        struct sockaddr_in server_address;

        // Create a socket on the internet using the tcp
        socket_address = socket ( AF_INET, SOCK_STREAM, 0 );
        if ( socket_address < 0 )
            throw std::runtime_error ( "Error in sockets::Server_socket::Server_socket : Couldn't open socket" );

        // Empty server_address
        bzero ( ( char* ) &server_address, sizeof ( server_address ) );
        // Use the internet
        server_address.sin_family = AF_INET;
        // Allow any incoming addresses
        server_address.sin_addr.s_addr = INADDR_ANY;
        // sin_port has to be in network byte order
        server_address.sin_port = htons ( port );

        // Enable socket address reuse
        int yes = 1;
        int success = setsockopt ( socket_address, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof ( int ) );
        if ( success < 0 )
            throw std::runtime_error ( "Error in sockets::Server_socket::Server_socket : setsockopt failed" );

        // server_address has to be converted to sockaddr* from sockadd_in
        success = bind ( socket_address, ( struct sockaddr* ) &server_address, sizeof ( server_address ) );
        if ( success < 0 )
            throw std::runtime_error ( "Error in sockets::Server_socket::Server_socket : Binding failed" );

        // Listen with a maximum backlog queue size of 5 ( seems to be standard )
        listen ( socket_address, 5 );
    }

    Client_socket Server_socket::next_socket ()
    {
        struct sockaddr_in client_address;
        unsigned int client_address_size = sizeof ( client_address );
        int client_socket = accept ( socket_address, ( struct sockaddr* ) &client_address, &client_address_size );
        if ( client_socket < 0 )
            throw std::runtime_error ( "Error in sockets::Server_socket::next_socket : Accepting failed" );

        return Client_socket ( client_socket );
    }

    void Server_socket::shutdown ()
    {
        int success = close ( socket_address );
        if ( success < 0 )
        {
            throw std::runtime_error ( "Error in sockets::Server_socket::shutdown : Shutting socket down failed");
        }
    }
}
