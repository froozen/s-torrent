#include <iostream>

#include "wrappers/sockets/client_socket.h"
#include "utils/json_element.h"

int main()
{
    sockets::Client_socket connection ( "127.0.0.1", 31005 );
    utils::Json_element introduction;
    introduction.set_string ( "name", "client" );
    connection.send ( introduction.to_small_string () );

    while ( true )
    {
        std::string line = connection.read_line ();
        try
        {
            utils::Json_element message ( line );
            std::cout << "The answer is: " + message.get_string ( "answer" ) << std::endl;
        }
        catch ( std::runtime_error& e )
        {
            std::cout << "Failed to parse json: " + line << std::endl;
        }
    }
    return 0;
}
