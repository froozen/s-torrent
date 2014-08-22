#include <gtest/gtest.h>

#include "wrappers/asio/client_socket.h"
#include "wrappers/asio/server_socket.h"

// I decided to put all tests in one file, because I can only
// test them together, anyways.

TEST ( AsioTest, GeneralTest )
{
    sockets::Server_socket server ( 12346 );
    sockets::Client_socket client ( "127.0.0.1", "12346" );
    sockets::Client_socket accepted = server.accept ();

    std::string lines [] = { "This is the first line.", "This is the second one.", "And now there is a third one." };

    // Send from client to server
    for ( int i = 0; i < 3; i++ )
    {
        client.send ( lines [ i ] );
    }
    for ( int i = 0; i < 3; i++ )
    {
        EXPECT_EQ ( lines [ i ], accepted.read_line () );
    }

    // Send from server to client
    for ( int i = 0; i < 3; i++ )
    {
        accepted.send ( lines [ i ] );
    }
    for ( int i = 0; i < 3; i++ )
    {
        EXPECT_EQ ( lines [ i ], client.read_line () );
    }

    // There should be a throw upon reading on a disconnected socket
    client.close ();
    EXPECT_THROW ( accepted.read_line (), std::runtime_error );

    // Connect to a ( hopefully ) noexistant host
    EXPECT_THROW ( sockets::Client_socket fail ( "adfkadsfjasjfdwefiasdfjvnasdf", "6445" ), std::runtime_error );
}
