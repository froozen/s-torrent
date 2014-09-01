#include <gtest/gtest.h>
#include "events/hub.h"
#include "events/connection_receiver.h"
#include "events/lambda_receiver.hpp"
#include "events/events.h"
#include "wrappers/sockets/server_socket.h"
#include "wrappers/sockets/client_socket.h"

#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

TEST ( ConnectionReceiverTest, GeneralTest )
{
    std::vector < std::string > received_strings;
    auto read_line_receiver = std::make_shared < events::Lambda_receiver < std::shared_ptr < events::Event > > > (
            [ & ] ( std::shared_ptr < events::Event > e ) {
                std::shared_ptr < events::Read_line_event > read_line_event = std::dynamic_pointer_cast < events::Read_line_event > ( e );
                received_strings.push_back ( read_line_event->get_line () );
            } );
    events::Hub::get_filter ( "Read_line_event" ).subscribe ( read_line_receiver );

    bool disconnected = false;
    auto connection_closed_receiver = std::make_shared < events::Lambda_receiver < std::shared_ptr < events::Event > > > (
            [ & ] ( std::shared_ptr < events::Event > e ) {
                disconnected = true;
            } );
    events::Hub::get_filter ( "Connection_closed_event" ).subscribe ( connection_closed_receiver );

    sockets::Server_socket server ( 12345 );
    events::Connection_receiver receiver ( "127.0.0.1", 12345 );
    receiver.start ();
    sockets::Client_socket connection = server.next_socket ();
    for ( int i = 0; i < 10; i++ )
    {
        connection.send ( std::to_string ( i ) );
    }

    // We need to wait a little bit, so we don't get an ugly segfault
    std::this_thread::sleep_for ( std::chrono::milliseconds ( 50 ) );
    for ( int i = 9; i > -1; i-- )
    {
        std::string received = received_strings.back ();
        EXPECT_EQ ( std::to_string ( i ), received );
        received_strings.pop_back ();
    }

    connection.shutdown ();
    std::this_thread::sleep_for ( std::chrono::milliseconds ( 50 ) );
    EXPECT_EQ ( disconnected, true );

    server.shutdown ();
}

TEST ( ConnectionReceiverTest, SendTest )
{
    sockets::Server_socket server ( 12345 );
    std::shared_ptr < events::Connection_receiver > receiver = std::make_shared < events::Connection_receiver > ( "127.0.0.1", 12345 );
    events::Hub::get_filter ( "Send_message_event" ).subscribe ( receiver );
    receiver->start ();
    sockets::Client_socket connection = server.next_socket ();

    std::shared_ptr < events::Event > event = std::make_shared < events::Send_message_event >
        ( "ConnectionReceiverTest -- sendTest", receiver.get () );

    events::Hub::send ( event );

    // We need to wait a little bit, so we don't get an ugly segfault
    std::this_thread::sleep_for ( std::chrono::milliseconds ( 50 ) );
    std::string received = connection.read_line ();
    EXPECT_EQ ( "ConnectionReceiverTest -- sendTest", received );

    connection.shutdown ();
    server.shutdown ();
}
