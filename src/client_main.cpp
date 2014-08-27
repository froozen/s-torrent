#include <iostream>

#include "wrappers/sockets/client_socket.h"
#include "utils/json_element.h"

int main()
{
    sockets::Client_socket connection ( "127.0.0.1", 31005 );
    utils::Json_element introduction;
    std::string url = "https://www.archlinux.org/releng/releases/2014.08.01/torrent/";
    introduction.set_string ( "url", url );
    connection.send ( introduction.to_small_string () );

    std::cout << "Added torrent: " + url << std::endl;

    return 0;
}
