#include "acceptor_hub.h"

namespace events
{
    std::vector < std::shared_ptr < Acceptor > > Acceptor_hub::acceptors;

    void Acceptor_hub::accept ( int port, std::string service )
    {
        std::shared_ptr < Acceptor > acceptor = std::make_shared < Acceptor > ( port, service );
        acceptors.push_back ( acceptor );
    }
}
