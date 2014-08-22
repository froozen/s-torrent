#include "acceptor_hub.h"
#include "wrappers/asio/client_socket.h"

#include <stdexcept>

namespace events
{
    std::map < std::string, std::shared_ptr < Acceptor > > Acceptor_hub::acceptors;

    void Acceptor_hub::accept ( int port, std::string service )
    {
        if ( acceptors.find ( service ) == acceptors.end () )
        {
            std::shared_ptr < Acceptor > acceptor = std::make_shared < Acceptor > ( port, service );
            acceptors.insert ( { service, acceptor } );
        }
        else
        {
            throw std::runtime_error ( "Error: service \"" + service + "\" already exists" );
        }
    }
}
