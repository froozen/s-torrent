#include "client_socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

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
            error ( "Client_socket : Couldn't open socket" );


        // Resolve server
        resolved_server = gethostbyname ( address.c_str () );
        if ( resolved_server == NULL )
            error ( "Client_socket : Host not found: \"" + address + "\"" );

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
            error ( "Client_socket : setsockopt failed" );

        // server_address has to be converted to sockaddr* from sockadd_in
        success = connect ( socket_address, ( struct sockaddr* ) &server_address, sizeof ( server_address ) );
        if ( success < 0 )
            error ( "Client_socket : Connecting failed");
    }

    Client_socket::Client_socket ( int socket_address ) :
        socket_address ( socket_address )
    {}

    std::string Client_socket::read_line ( std::string linebreak )
    {
        // Read until we have at least one line
        while ( next_lines.empty () )
        {
            // This might actually happen ( look at the test for an example )
            if ( ends_with ( line_rest, linebreak ) )
            {
                // Remove the linebreak from the end
                next_lines.push_back ( line_rest.substr ( 0, line_rest.find_last_of ( linebreak ) ) );
                line_rest = "";
                break;
            }

            char buffer [ 1024 ];
            int success = read ( socket_address, buffer, sizeof ( buffer ) - 1 );
            if ( success < 0 )
                error ( "read_line : Reading from socket failed");
            else if ( success == 0 )
                error ( "read_line : Connection closed");
            buffer [ success ] = '\0';

            // Create actual string from vector
            std::string data_string ( buffer, strlen ( buffer ) );

            std::string line;
            // Split lines at delimiter
            while ( ( line = get_line ( data_string, linebreak ) ).size () > 0 )
            {
                // Apply line_rest ( if any )
                line = line_rest + line;
                line_rest.clear ();
                // Save yourself the hassle of dealing with DOS linebreaks
                next_lines.push_back ( line );
            }

            // If buffer_string doesn't end with a linebreak
            if ( data_string.size () > 0 )
            {
                // Create a line_rest
                line_rest += data_string;
            }
        }

        // Return next line
        while ( !next_lines.empty () && next_lines.front () == "" )
            next_lines.pop_front ();

        if ( !next_lines.empty () )
        {
            std::string line = next_lines.front ();
            next_lines.pop_front ();
            return line;
        }
        else
            return read_line ();
     }

    void Client_socket::send ( std::string message, std::string linebreak )
    {
        message += linebreak;
        int success = write ( socket_address, message.c_str (), message.size () );
        if ( success < 0 )
            error ( "send : Sending over socket failed");
    }

    void Client_socket::shutdown ()
    {
        int success = close ( socket_address );
        if ( success < 0 )
            error ( "shutdown : Shutting socket down failed" );
    }

    void Client_socket::error ( std::string message )
    {
        if ( errno != 0 )
            throw std::runtime_error ( "Error in sockets::Client_socket::" + message + " ( " + strerror ( errno ) + " )" );
        else
            throw std::runtime_error ( "Error in sockets::Client_socket::" + message );
    }

    std::string Client_socket::get_line ( std::string& from, const std::string& delimiter )
    {
        size_t pos = from.find ( delimiter );
        if ( pos != std::string::npos )
        {
            std::string return_string = from.substr ( 0, pos );
            from = from.substr ( pos + delimiter.size () );
            return return_string;
        }
        return "";
    }

    bool Client_socket::ends_with ( const std::string& target, const std::string& ending )
    {
        if ( target.length () >= ending.length () )
            return ( 0 == target.compare ( target.length () - ending.length (), ending.length (), ending ) );
        return false;
    }
}
