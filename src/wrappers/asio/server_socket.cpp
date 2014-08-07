#include "server_socket.h"

using boost::asio::ip::tcp;

Server_socket::Server_socket ( int port ) :
    io_service ( std::make_shared < boost::asio::io_service > () ),
    acceptor ( *io_service, tcp::endpoint ( tcp::v4 (), port ) )
{}

Client_socket Server_socket::accept ()
{
    std::unique_ptr < tcp::socket > socket ( new tcp::socket ( *io_service ) );
    acceptor.accept ( *socket );
    return Client_socket ( std::move ( socket ), io_service );
}
