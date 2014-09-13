#include <memory>
#include <iostream>
#include <cstring>

#include "client/event_system.h"
#include "client/client_interface.h"
#include "client/events/events.h"
#include "events/connection_receiver.h"
#include "events/hub.h"

bool parse_args ( int argc, char** argv )
{
    if ( argc > 1 )
    {
        if ( ( !strcmp ( argv [ 1 ], "--url" ) ) && argc > 2 )
        {
            for ( int i = 2; i < argc; i++ )
            {
                auto add_torrent_event = std::make_shared < client::Add_torrent_event > ( client::Add_torrent_event::Method::URL, argv [ i ] );
                events::Hub::send ( add_torrent_event );
                std::cout << "Added: " << argv [ i ] << std::endl;
            }
        }
        else
        {
            for ( int i = 1; i < argc; i++ )
            {
                auto add_torrent_event = std::make_shared < client::Add_torrent_event > ( client::Add_torrent_event::Method::FILE, argv [ i ] );
                events::Hub::send ( add_torrent_event );
                std::cout << "Added: " << argv [ i ] << std::endl;
            }
        }
        return false;
    }
    else
        return true;
}

int main ( int argc, char** argv )
{
    auto connection = std::make_shared < events::Connection_receiver > ( "localhost", 31005 );
    events::Hub::get_filter ( "Send_message_event" ).subscribe ( connection );
    client::Event_system::initialize ( connection.get () );
    connection->start ();

    if ( parse_args ( argc, argv ) )
        client::Interface::run ( connection.get () );

    std::exit ( 0 );
}
