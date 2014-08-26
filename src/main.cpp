#include <iostream>
#include "wrappers/sockets/client_socket.h"

int main()
{
    // sockets::Client_socket c ( "irc.freenode.net", 6667 );
    sockets::Client_socket c ( "127.0.0.1", 6667 );
    std::cout << c.read_line () << std::endl;
    return 0;
}
