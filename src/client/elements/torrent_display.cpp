#include "torrent_display.h"

#include "client/shared_data.h"

#include <iostream>

namespace client
{
    void Torrent_display_element::update ( char key, std::shared_ptr < ncurses::Window > window )
    {
        auto torrent_data = client::Shared_data::get_torrent_data ();
        if ( torrent_data.get () != nullptr )
        {
            for ( auto torrent : *torrent_data )
            {
                int y = 0;
                if ( torrent->is_active () )
                {
                    window->move ( 0, y );
                    window->draw_string ( torrent->get_string ( "name" ) );
                    y ++;

                    if ( torrent->get_double ( "progress" ) < 1 )
                    {
                        draw_progress ( torrent, window, y );
                        y ++;
                    }

                    if ( torrent->get_int ( "download_payload_rate" ) > 0 )
                    {
                        draw_download ( torrent, window, y );
                        y++;
                    }

                    if ( torrent->get_int ( "upload_payload_rate" ) > 0 )
                    {
                        draw_upload ( torrent, window, y );
                        y++;
                    }

                    y++;
                }
            }
            window->move ( window->get_width () - 1, window->get_height () - 1 );
            window->refresh ();
        }
    }

    int Torrent_display_element::get_prefered_width () const { return 0; }
    int Torrent_display_element::get_prefered_height () const { return 0; }

    std::string Torrent_display_element::right_bound ( std::string text, size_t amount )
    {
        while ( text.size () < amount )
            text = " " + text;
        return text;
    }

    void Torrent_display_element::draw_progress (
            std::shared_ptr < Torrent_data >& torrent_data,
            std::shared_ptr < ncurses::Window > window,
            int y
            )
    {
        std::string progress_number = torrent_data->get_percentage ( "progress" );
        std::string file_size = torrent_data->get_file_size ( "total_wanted" );

        window->move ( 0, y );
        window->draw_string ( right_bound ( progress_number, 10 ) + " of " + file_size );
    }


    void Torrent_display_element::draw_download (
            std::shared_ptr < Torrent_data >& torrent_data,
            std::shared_ptr < ncurses::Window > window,
            int y
            )
    {
        std::string download_speed = torrent_data->get_transfer_speed ( "download_payload_rate" );
        std::string eta = torrent_data->get_eta ();

        window->move ( 0, y );
        window->set_fg_color ( ncurses::Window::RED );
        window->draw_string ( right_bound ( download_speed, 14 ) );
        window->set_fg_color ( ncurses::Window::DEFAULT );
        window->draw_string ( right_bound ( eta, 16 ) );
    }

    void Torrent_display_element::draw_upload (
            std::shared_ptr < Torrent_data >& torrent_data,
            std::shared_ptr < ncurses::Window > window,
            int y
            )
    {
        std::string upload_speed = torrent_data->get_transfer_speed ( "upload_payload_rate" );
        std::string ratio = torrent_data->get_ratio ();

        window->move ( 0, y );
        window->set_fg_color ( ncurses::Window::GREEN );
        window->draw_string ( right_bound ( upload_speed, 14 ) );
        window->set_fg_color ( ncurses::Window::DEFAULT );
        window->draw_string ( right_bound ( ratio, 16 ) );
    }
}
