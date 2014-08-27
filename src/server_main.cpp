#define BOOST_ASIO_DYN_LINK

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "events/acceptor_hub.h"
#include "events/hub.h"
#include "events/events.h"
#include "events/lambda_receiver.hpp"

#include "utils/json_element.h"

#include "torrent/session.h"

void on_receive ( std::shared_ptr < events::Event > event )
{
    auto read_line_event = std::dynamic_pointer_cast < events::Read_line_event > ( event );
    try
    {
        utils::Json_element received_json ( read_line_event->get_line () );
        std::string url = received_json.get_string ( "url" );
        if ( url != "None" )
        {
            libtorrent::add_torrent_params p;
            p.save_path = "./";
            p.url = url;
            libtorrent::torrent_handle added = torrent::Session::add_torrent ( p );
            added.set_download_limit ( 35000 );
            std::cout << "Started downloading: " + url << std::endl;
        }
    }
    catch ( std::runtime_error& e )
    {}
}
void setup ()
{
    torrent::Session::initialize ();
    auto on_receive_receiver = std::make_shared < events::Lambda_receiver < std::shared_ptr < events::Event > > > ( &on_receive );
    events::Hub::get_filter ( "Read_line_event" ).subscribe ( on_receive_receiver );
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
