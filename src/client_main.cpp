#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <memory>

#include "wrappers/sockets/client_socket.h"
#include "utils/json_element.h"
#include "utils/json_list_element.h"

int main()
{
    sockets::Client_socket connection ( "127.0.0.1", 31005 );
    utils::Json_element introduction;
    std::string url = "https://www.archlinux.org/releng/releases/2014.08.01/torrent/";
    introduction.set_string ( "url", url );
    introduction.set_string ( "type", "Add_torrent_event" );
    connection.send ( introduction.to_small_string () );

    std::cout << "Added torrent: " + url << std::endl;

    while ( true )
    {
        utils::Json_element event;
        event.set_string ( "type", "Torrent_data_requested_event" );
        connection.send ( event.to_small_string () );

        utils::Json_element answer_event ( connection.read_line () );
        std::shared_ptr < utils::Json_list_element > torrents = answer_event.get_list_element ( "torrent_data" );
        for ( int i = 0; i < torrents->size (); i++ )
        {
            std::shared_ptr < utils::Json_element > torrent = torrents->get_element ( i );
            std::cout << "[ " << torrent->get_string ( "state" ) << " ] " <<  torrent->get_string ( "name" ) << std::endl;
            std::cout << "Download: " <<  ( torrent->get_int ( "download_payload_rate" ) / 1000 ) << " KiB"
               << " Upload: " << ( torrent->get_int ( "upload_payload_rate" ) / 1000 ) << " KiB [ " <<
               std::fixed << std::setprecision ( 2 ) << torrent->get_double ( "progress" ) * 100 << "% ]"
               << std::endl << std::endl;
        }

        std::this_thread::sleep_for ( std::chrono::seconds ( 8 ) );
    }

    return 0;
}
