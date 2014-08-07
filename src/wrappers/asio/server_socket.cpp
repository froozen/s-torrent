#include "server_socket.h"
#include <boost/exception/diagnostic_information.hpp>

using boost::asio::ip::tcp;

namespace sockets
{
    Server_socket::Server_socket ( int port ) :
        io_service ( std::make_shared < boost::asio::io_service > () ),
        acceptor ( *io_service, tcp::endpoint ( tcp::v4 (), port ) )
    {}

    Client_socket Server_socket::accept ()
    {
        try
        {
            std::unique_ptr < tcp::socket > socket ( new tcp::socket ( *io_service ) );
            acceptor.accept ( *socket );
            return Client_socket ( std::move ( socket ), io_service );
        }
        catch ( boost::exception& e )
        {
            throw std::runtime_error ( boost::diagnostic_information ( e ) );
        }
    }
}
