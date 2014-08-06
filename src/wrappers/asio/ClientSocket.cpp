#include "ClientSocket.h"

#include <sstream>

using boost::asio::ip::tcp;

ClientSocket ClientSocket::create ( std::string address, std::string service )
{
    return ClientSocket ( address, service );
};

ClientSocket::ClientSocket ( std::string address, std::string service ) :
    io_service ( new boost::asio::io_service ),
    socket ( *io_service )
{
    tcp::resolver resolver ( *io_service );
    tcp::resolver::query query ( address, service );
    tcp::resolver::iterator endpoint_iterator = resolver.resolve ( query );

    boost::asio::connect ( socket, endpoint_iterator );
}

std::string ClientSocket::read_line ()
{
    while ( next_lines.empty () )
    {
        std::vector < char > buffer ( 1024 );
        boost::system::error_code error;

        size_t len = socket.read_some ( boost::asio::buffer ( buffer ), error );

        if ( error )
            throw boost::system::system_error ( error );

        std::string data_string = std::string ( buffer.begin (), buffer.begin () + len );

        std::string line;
        std::stringstream ss ( std::string ( buffer.begin (), buffer.begin () + len ) );
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

        if ( buffer.back () != '\n' )
        {
            line_rest = next_lines.back ();
            next_lines.pop_back ();
        }
    }

    std::string line = next_lines.front ();
    next_lines.pop_front ();
    return line;
}

void ClientSocket::send ( std::string message )
{
    boost::system::error_code error;
    boost::asio::write ( socket, boost::asio::buffer ( message ), error );

    if ( error )
        throw boost::system::system_error ( error );
}
