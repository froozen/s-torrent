#include "torrent_display.h"

#include "client/shared_data.h"
#include "client/data_formatting.h"

#include <algorithm>

namespace client
{
    void Torrent_display_element::update ( char key, std::shared_ptr < ncurses::Window > window )
    {
        auto torrent_data = client::Shared_data::get_torrent_data ();
        if ( torrent_data != nullptr )
        {
            int y = 0;
            draw_totals ( torrent_data, window, y );
            y += 2;

            for ( auto torrent : *torrent_data )
            {
                // I try to limit the displayed lines as much as possible, to display as much relevant
                // information in a small terminal window as possible
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

    // Pad the string with spaces in the front until they reach a certain size
    // right_boud ( "hello", 8 ) --> "   hello"
    std::string Torrent_display_element::right_bound ( std::string text, size_t amount )
    {
        while ( text.size () < amount )
            text = " " + text;
        return text;
    }

    // Display progress percentage, total torrent size and progress bar
    void Torrent_display_element::draw_progress (
            std::shared_ptr < Torrent_data >& torrent_data,
            std::shared_ptr < ncurses::Window > window,
            int y
            )
    {
        std::string progress_number = to_percentage ( torrent_data->get_double ( "progress" ) );
        std::string file_size = to_file_size ( torrent_data->get_double ( "total_wanted" ) );
        std::string progress_text =  right_bound ( progress_number, 10 ) + " of " + file_size + " [";

        window->move ( 0, y );
        window->draw_string ( progress_text );

        int bar_width = window->get_width () - 2 - progress_text.size ();
        window->set_fg_color ( ncurses::Window::CYAN );
        for ( int i = 0; i < bar_width * torrent_data->get_double ( "progress" ); i++ )
        {
            window->draw_string ( "|" );
        }
        window->set_fg_color ( ncurses::Window::DEFAULT );
        window->move ( window->get_width () - 1, y );
        window->draw_string ( "]" );
    }


    // Display download speed, eta and seed count
    void Torrent_display_element::draw_download (
            std::shared_ptr < Torrent_data >& torrent_data,
            std::shared_ptr < ncurses::Window > window,
            int y
            )
    {
        std::string download_speed = to_transfer_speed ( torrent_data->get_int ( "download_payload_rate" ) );
        std::string eta = torrent_data->get_eta ();
        std::string num_seeds = "( " + std::to_string ( torrent_data->get_int ( "num_seeds" ) ) + " )";

        window->move ( 0, y );
        window->set_fg_color ( ncurses::Window::RED );
        window->draw_string ( right_bound ( download_speed, 14 ) );
        window->set_fg_color ( ncurses::Window::DEFAULT );
        window->draw_string ( right_bound ( eta, 16 ) );
        window->draw_string ( right_bound ( num_seeds, 10 ) );
    }

    // Display upload speed and ratio
    void Torrent_display_element::draw_upload (
            std::shared_ptr < Torrent_data >& torrent_data,
            std::shared_ptr < ncurses::Window > window,
            int y
            )
    {
        std::string upload_speed = to_transfer_speed ( torrent_data->get_int ( "upload_payload_rate" ) );
        std::string ratio = torrent_data->get_ratio ();

        window->move ( 0, y );
        window->set_fg_color ( ncurses::Window::GREEN );
        window->draw_string ( right_bound ( upload_speed, 14 ) );
        window->set_fg_color ( ncurses::Window::DEFAULT );
        window->draw_string ( right_bound ( ratio, 16 ) );
    }

    // Display total upload- and download speed and a message if the client has disconnected
    void Torrent_display_element::draw_totals (
            std::shared_ptr < std::vector < std::shared_ptr < Torrent_data > > >& torrent_data,
            std::shared_ptr < ncurses::Window > window,
            int y
            )
    {
        int total_download = 0;
        int total_upload = 0;
        for ( auto torrent : *torrent_data )
        {
            total_download += torrent->get_int ( "download_payload_rate" );
            total_upload += torrent->get_int ( "upload_payload_rate" );
        }

        window->move ( 0, y );
        window->draw_string ( "Download: " );
        window->set_fg_color ( ncurses::Window::RED );
        window->draw_string ( right_bound ( to_transfer_speed ( total_download ), 14 ) );
        window->set_fg_color ( ncurses::Window::DEFAULT );
        window->draw_string ( "   Upload: " );
        window->set_fg_color ( ncurses::Window::GREEN );
        window->draw_string ( right_bound ( to_transfer_speed ( total_upload ), 14 ) );
        window->set_fg_color ( ncurses::Window::DEFAULT );

        if ( !client::Shared_data::get_connected () )
        {
            std::string message = "[ DISCONNECTED ]";
            window->move ( std::max ( 0, window->get_width () - static_cast < int > ( message.size () ) ), y );
            window->set_fg_color ( ncurses::Window::RED );
            window->draw_string ( message );
            window->set_fg_color ( ncurses::Window::DEFAULT );
        }
    }
}
