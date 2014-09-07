#include <memory>
#include <chrono>
#include <thread>

#include "client/event_system.h"
#include "client/shared_data.h"
#include "events/connection_receiver.h"
#include "events/hub.h"
#include "events/events.h"
#include "utils/json.h"

#include "wrappers/ncurses/session.h"
#include "wrappers/ncurses/panel.h"
#include "wrappers/ncurses/stretch.h"
#include "wrappers/ncurses/orientation.h"
#include "client/elements/torrent_display.h"

int main()
{
    client::Event_system::initialize ();
    auto connection = std::make_shared < events::Connection_receiver > ( "localhost", 31005 );
    connection->start ();
    events::Hub::get_filter ( "Send_message_event" ).subscribe ( connection );

    utils::Json_element add_torrent;
    add_torrent.set_string ( "type", "Add_torrent_event" );
    add_torrent.set_string ( "url", "https://www.archlinux.org/releng/releases/2014.08.01/torrent/" );
    events::Hub::send ( std::make_shared < events::Send_message_event > ( add_torrent.to_small_string (), connection.get () ) );

    utils::Json_element torrent_data_request;
    torrent_data_request.set_string ( "type", "Torrent_data_requested_event" );
    events::Hub::send ( std::make_shared < events::Send_message_event > ( torrent_data_request.to_small_string (), connection.get () ) );

    ncurses::Session session;
    auto torrent_display = std::make_shared < client::Torrent_display_element > ();
    session.set_root ( torrent_display );

    client::Shared_data::set_run ( true );
    while ( client::Shared_data::get_run () )
        session.update ();

    session.end ();
    std::exit ( 0 );
}
