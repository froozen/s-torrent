#ifndef ACCEPTOR_HUB_GUARD
#define ACCEPTOR_HUB_GUARD

#include "acceptor.h"

#include <string>
#include <vector>
#include <memory>

namespace events
{
    class Acceptor_hub
    {
        public:
            static void accept ( int port, std::string service = "" );

        private:
            static std::vector < std::shared_ptr < Acceptor > > acceptors;
    };
}

#endif //ACCEPTOR_HUB_GUARD
