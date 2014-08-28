#include <memory>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

#include "client/event_system.h"
#include "client/shared_data.h"
#include "events/connection_receiver.h"
#include "events/hub.h"
#include "events/events.h"
#include "utils/json_element.h"

int main()
{
    client::Event_system::initialize ();
    auto connection = std::make_shared < events::Connection_receiver > ( "localhost", 31005 );
    connection->start ();
    events::Hub::get_filter ( "Send_message_event" ).subscribe ( connection );

    std::cout << "Connected." << std::endl;

    utils::Json_element add_torrent;
    add_torrent.set_string ( "type", "Add_torrent_event" );
    add_torrent.set_string ( "url", "https://www.archlinux.org/releng/releases/2014.08.01/torrent/" );
    events::Hub::send ( std::make_shared < events::Send_message_event > ( add_torrent.to_small_string (), connection.get () ) );

    utils::Json_element torrent_data_request;
    torrent_data_request.set_string ( "type", "Torrent_data_requested_event" );
    events::Hub::send ( std::make_shared < events::Send_message_event > ( torrent_data_request.to_small_string (), connection.get () ) );

    std::cout << "Sent events" << std::endl;

    while ( true )
    {
        std::this_thread::sleep_for ( std::chrono::seconds ( 3 ) );
        auto torrent_data = client::Shared_data::get_torrent_data ();
        if ( torrent_data.get () != nullptr )
        {
            for ( auto torrent : *torrent_data )
            {
                std::cout << torrent->get_string ( "name" ) << std::endl;
                std::cout << std::fixed << std::setprecision ( 2 ) <<
                    torrent->get_double ( "progress" ) * 100 << "%" << std::endl << std::endl;
            }
        }
    }

    return 0;
}
