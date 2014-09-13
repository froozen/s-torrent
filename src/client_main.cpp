#include <memory>
#include <chrono>
#include <thread>

#include "client/event_system.h"
#include "client/shared_data.h"
#include "events/connection_receiver.h"
#include "events/hub.h"
#include "events/events.h"
#include "client/events/events.h"
#include "utils/json.h"

#include "wrappers/ncurses/session.h"
#include "wrappers/ncurses/panel.h"
#include "wrappers/ncurses/stretch.h"
#include "wrappers/ncurses/orientation.h"
#include "client/elements/torrent_display.h"

int main()
{
    auto connection = std::make_shared < events::Connection_receiver > ( "localhost", 31005 );
    events::Hub::get_filter ( "Send_message_event" ).subscribe ( connection );
    client::Event_system::initialize ( connection.get () );
    connection->start ();

    utils::Json_element torrent_data_request;
    torrent_data_request.set_string ( "type", "Torrent_data_requested_event" );
    events::Hub::send ( std::make_shared < events::Send_message_event > ( torrent_data_request.to_small_string (), connection.get () ) );

    ncurses::Session session;
    auto torrent_display = std::make_shared < client::Torrent_display_element > ();
    session.set_root ( torrent_display );

    client::Shared_data::set_run ( true );
    client::Shared_data::set_connected ( true );
    while ( client::Shared_data::get_run () )
        session.update ();

    session.end ();
    std::exit ( 0 );
}
