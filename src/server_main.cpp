#define BOOST_ASIO_DYN_LINK

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "events/acceptor_hub.h"
#include "events/hub.h"
#include "events/events.h"

#include "utils/json.h"
#include "utils/configuration.h"

#include "torrent/session.h"
#include "torrent/state.h"
#include "torrent/event_system.h"
#include "torrent/torrent_data_to_json.h"
#include "torrent/alert_event_creator.h"

int main ()
{
    utils::Configuration::load ( "config.json" );
    if ( utils::Configuration::get_root ()->get_int ( "server_port" ) < 0 )
    {
        std::cout << "Invalid server_port" << std::endl;
        std::cout << "Exiting..." << std::endl;
        std::exit ( 0 );
    }
    torrent::Session::initialize ();
    torrent::State::load ();
    torrent::Session::load_torrent_states ();
    torrent::Event_system::initialize ();
    events::Acceptor_hub::accept ( utils::Configuration::get_root ()->get_int ( "server_port" ), "listening port" );

    torrent::Alert_event_creator aec;
    aec.start ();

    while ( true )
    {
        std::vector < libtorrent::torrent_handle > torrents = torrent::Session::get_torrents ();
        for ( auto torrent : torrents )
        {
            libtorrent::torrent_status status = torrent.status ();
            std::cout << torrent.name () << std::endl;
            std::cout << "Down: " << ( status.download_payload_rate / 1000 ) << " KiB " <<
               "Up: " << ( status.upload_payload_rate / 1000 ) << " KiB" << std::endl << std::endl;
        }

        if ( torrents.empty () )
            std::cout << "No torrents..." << std::endl;

        std::this_thread::sleep_for ( std::chrono::seconds ( 5 ) );
    }

    return 0;
}
