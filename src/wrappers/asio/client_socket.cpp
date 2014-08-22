#include "client_socket.h"

#include <sstream>
#include <stdexcept>
#include <boost/exception/diagnostic_information.hpp>

using boost::asio::ip::tcp;

namespace sockets
{
    Client_socket::Client_socket ( std::string address, std::string service ) :
        io_service ( std::make_shared < boost::asio::io_service > () ),
        socket ( new tcp::socket ( *io_service ) )
    {
        try
        {
            // Resolve address
            tcp::resolver resolver ( *io_service );
            tcp::resolver::query query ( address, service );
            tcp::resolver::iterator endpoint_iterator = resolver.resolve ( query );

            // Connect to address
            boost::asio::connect ( *socket, endpoint_iterator );
        }
        catch ( boost::exception& e )
        {
            throw std::runtime_error ( boost::diagnostic_information ( e ) );
        }
    }

    // Simple constructor used by Server_socket
    Client_socket::Client_socket (
            std::unique_ptr < tcp::socket >&& socket,
            std::shared_ptr < boost::asio::io_service > io_service
            ) :
        io_service ( io_service ),
        socket ( std::move ( socket ) )
    {}

    std::string Client_socket::read_line ()
    {
        // Read until we have at least one line
        while ( next_lines.empty () )
        {
            std::vector < char > buffer ( 1024 );
            size_t len;

            try
            {
                len = ( *socket ).read_some ( boost::asio::buffer ( buffer ) );
            }
            catch ( boost::exception& e )
            {
                throw std::runtime_error ( boost::diagnostic_information ( e ) );
            }

            // Create actual string from vector
            std::string data_string = std::string ( buffer.begin (), buffer.begin () + len );

            std::string line;
            std::string buffer_string = std::string ( buffer.begin (), buffer.begin () + len );
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
        try
        {
            boost::asio::write ( *socket, boost::asio::buffer ( message + "\n" ) );
        }
        catch ( boost::exception& e )
        {
            throw std::runtime_error ( boost::diagnostic_information ( e ) );
        }
    }

    void Client_socket::close ()
    {
        try
        {
            socket->shutdown ( tcp::socket::shutdown_both );
            socket->close ();
        }
        catch ( boost::exception& e )
        {
            throw std::runtime_error ( boost::diagnostic_information ( e ) );
        }
    }
}
