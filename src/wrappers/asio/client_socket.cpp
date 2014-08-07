#include "client_socket.h"

#include <sstream>

using boost::asio::ip::tcp;

Client_socket::Client_socket ( std::string address, std::string service ) :
    io_service ( std::make_shared < boost::asio::io_service > () ),
    socket ( new tcp::socket ( *io_service ) )
{
    tcp::resolver resolver ( *io_service );
    tcp::resolver::query query ( address, service );
    tcp::resolver::iterator endpoint_iterator = resolver.resolve ( query );

    boost::asio::connect ( *socket, endpoint_iterator );
}

Client_socket::Client_socket (
        std::unique_ptr < tcp::socket >&& socket,
        std::shared_ptr < boost::asio::io_service > io_service
        ) :
    io_service ( io_service ),
    socket ( std::move ( socket ) )
{}

std::string Client_socket::read_line ()
{
    while ( next_lines.empty () )
    {
        std::vector < char > buffer ( 1024 );

        size_t len = ( *socket ).read_some ( boost::asio::buffer ( buffer ) );

        std::string data_string = std::string ( buffer.begin (), buffer.begin () + len );

        std::string line;
        std::string buffer_string = std::string ( buffer.begin (), buffer.begin () + len );
        std::stringstream ss ( buffer_string );
        while ( ( std::getline ( ss, line, '\n' ) ) )
        {
            line = line_rest + line;
            line_rest.clear ();
            while ( line.back () == '\n' || line.back () == '\r' )
            {
                line.pop_back ();
            }
            next_lines.push_back ( line );
        }

        if ( buffer_string.back () != '\n' )
        {
            line_rest = next_lines.back ();
            next_lines.pop_back ();
        }
    }

    std::string line = next_lines.front ();
    next_lines.pop_front ();
    return line;
}

void Client_socket::send ( std::string message )
{
    boost::asio::write ( *socket, boost::asio::buffer ( message ) );
}
