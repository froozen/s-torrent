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
#include "torrent/event_system.h"
#include "torrent/torrent_data_to_json.h"

void setup ()
{
    torrent::Session::initialize ();
    torrent::Event_system::initialize ();
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
                std::cout << "\n" << torrent::to_json ( torrent ).to_formatted_string () << std::endl;
            }
        }

        else
            std::cout << "No torrents..." << std::endl;

        std::this_thread::sleep_for ( std::chrono::seconds ( 5 ) );
    }

    return 0;
}
