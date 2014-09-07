#include "session.h"

#include <ncurses.h>

#include <stdexcept>

namespace ncurses
{
    bool Session::created;

    Session::Session ()
    {
        if ( !created )
        {
            created = true;

            // Standard ncurses init methods
            initscr ();
            // Update every 2.5 seconds
            halfdelay ( 25 );
            noecho ();
            start_color ();
            use_default_colors ();
            refresh ();

            int max_x, max_y;
            getmaxyx ( stdscr, max_y, max_x );
            window = std::make_shared < Window > ( 0, 0, max_x, max_y );

            // Initialize all possible color combinations, using a simple calculation
            // This enables us to change the colors in Window in a comfortable way
            for ( int fg = -1; fg < 8; fg++ )
            {
                for ( int bg = -1; bg < 8; bg++ )
                {
                    init_pair ( 2 + fg + 8 * ( 1 + bg ), fg, bg );
                }
            }
        }
        else
            throw std::runtime_error ( "Error in ncurses::Session::Session : Session already created" );
    }

    Session::Session ( const std::shared_ptr < Element >& root ) :
        Session ()
    {
        this->root = root;
    }

    Session::~Session ()
    {
        created = false;
    }

    void Session::update ()
    {
        char input = getch ();
        int max_x, max_y;
        getmaxyx ( stdscr, max_y, max_x );
        if ( max_x != window->get_width () || max_y != window->get_height () )
            window->resize ( max_x, max_y );

        if ( root != nullptr )
        {
            root->update ( input, window );
        }
    }

    void Session::end ()
    {
        endwin ();
    }

    void Session::set_root ( const std::shared_ptr < Element >& root )
    {
        this->root = root;
    }

    std::shared_ptr < Element > Session::get_root ()
    {
        return root;
    }
}
