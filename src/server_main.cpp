#define BOOST_ASIO_DYN_LINK

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "events/acceptor_hub.h"
#include "events/hub.h"
#include "events/events.h"

#include "utils/json_element.h"

#include "torrent/session.h"
#include "torrent/receivers/event_converter.h"
#include "torrent/receivers/add_torrent_receiver.h"

void setup ()
{
    torrent::Session::initialize ();

    auto event_converter = std::make_shared < torrent::Event_converter > ();
    events::Hub::get_filter ( "Read_line_event" ).subscribe ( event_converter );

    auto add_torrent_receiver = std::make_shared < torrent::Add_torrent_receiver > ();
    events::Hub::get_filter ( "Add_torrent_event" ).subscribe ( add_torrent_receiver );

    events::Acceptor_hub::accept ( 31005, "listening port" );
}

int main ()
{
    setup ();

    while ( true )
    {
        std::vector < libtorrent::torrent_handle > torrents = torrent::Session::get_torrents ();
        if ( !torrents.empty () )
        {
            for ( auto torrent : torrents )
            {
                libtorrent::torrent_status status = torrent.status ();
                std::cout << torrent.name () << std::endl;
                std::cout << "Down: " << ( status.download_payload_rate / 1000 ) << " KiB " <<
                   "Up: " << ( status.upload_payload_rate / 1000 ) << " KiB" <<  std::endl << std::endl;
            }
        }

        else
            std::cout << "No torrents..." << std::endl;

        std::this_thread::sleep_for ( std::chrono::seconds ( 5 ) );
    }

    return 0;
}
