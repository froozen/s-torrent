#include "client_socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include <sstream>
#include <stdexcept>

namespace sockets
{
    Client_socket::Client_socket ( std::string address, int port )
    {
        struct sockaddr_in server_address;
        struct hostent* resolved_server;

        // Create a socket on the internet using the tcp
        socket_address = socket(AF_INET, SOCK_STREAM, 0);
        if ( socket_address < 0 )
            throw std::runtime_error ( "Error in sockets::Client_socket::Client_socket : Couldn't open socket" );


        // Resolve server
        resolved_server = gethostbyname ( address.c_str () );
        if ( resolved_server == NULL )
            throw std::runtime_error ( "Error in sockets::Client_socket::Client_socket : Host not found: \"" + address + "\"" );

        // Empty server_address
        bzero ( ( char* ) &server_address, sizeof ( server_address ) );
        // Use the internet
        server_address.sin_family = AF_INET;
        // Use address of resolved server
        bcopy ( ( char* ) resolved_server->h_addr, ( char* ) &server_address.sin_addr.s_addr, resolved_server->h_length );
        // sin_port has to be in network byte order
        server_address.sin_port = htons ( port );

        // Enable socket address reuse
        int yes = 1;
        int success = setsockopt ( socket_address, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof ( int ) );
        if ( success < 0 )
            throw std::runtime_error ( "Error in sockets::Client_socket::Client_socket : setsockopt failed" );

        // server_address has to be converted to sockaddr* from sockadd_in
        success = connect ( socket_address, ( struct sockaddr* ) &server_address, sizeof ( server_address ) );
        if ( success < 0 )
            throw std::runtime_error ( "Error in sockets::Client_socket::Client_socket : Connecting failed");
    }

    Client_socket::Client_socket ( int socket_address ) :
        socket_address ( socket_address )
    {}

    std::string Client_socket::read_line ()
    {
        // Read until we have at least one line
        while ( next_lines.empty () )
        {
            char buffer [ 1024 ];
            int success = read ( socket_address, buffer, sizeof ( buffer ) - 1 );
            if ( success < 0 )
                throw std::runtime_error ( "Error in sockets::Client_socket::read_line : Reading from socket failed");
            else if ( success == 0 )
                throw std::runtime_error ( "Error in sockets::Client_socket::read_line : Connection closed");

            // Create actual string from vector
            std::string data_string ( buffer, strlen ( buffer ) );

            std::string line;
            std::string buffer_string = data_string;
            std::stringstream ss ( buffer_string );
            // Split lines at '\n'
            while ( ( std::getline ( ss, line, '\n' ) ) )
            {
                // Apply line_rest ( if any )
                line = line_rest + line;
                line_rest.clear ();
                // Save yourself the hassle of dealing with DOS linebreaks
                while ( line.back () == '\r' )
                {
                    line.pop_back ();
                }
                next_lines.push_back ( line );
            }

            // If buffer_string doesn't end with an '\n'
            if ( buffer_string.back () != '\n' )
            {
                // Create a line_rest
                line_rest = next_lines.back ();
                next_lines.pop_back ();
            }
        }

         // Return next line
         std::string line = next_lines.front ();
         next_lines.pop_front ();
         return line;
     }

    void Client_socket::send ( std::string message )
    {
        message += "\n";
        int success = write ( socket_address, message.c_str (), message.size () );
        if ( success < 0 )
            throw std::runtime_error ( "Error in sockets::Client_socket::send : Sending over socket failed");
    }

    void Client_socket::shutdown ()
    {
        int success = close ( socket_address );
        if ( success < 0 )
            throw std::runtime_error ( "Error in sockets::Client_socket::shutdown : Shutting socket down failed");
    }
}
