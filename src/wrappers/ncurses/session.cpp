#include "session.h"

#include <ncurses.h>

namespace ncurses
{
    std::shared_ptr < Panel > Session::panel;

    void Session::init ()
    {
        // Standard ncurses init methods
        initscr ();
        // Update every 2.5 seconds
        halfdelay ( 25 );
        noecho ();
        start_color ();
        use_default_colors ();
        refresh ();

        // Initialize all possible color combinations, using a simple calculation
        // This enables us to change the colors in Window way comfortably than any
        // other solution
        for ( int fg = -1; fg < 8; fg++ )
        {
            for ( int bg = -1; bg < 8; bg++ )
            {
                init_pair ( 2 + fg + 8 * ( 1 + bg ), fg, bg );
            }
        }
    }

    void Session::end ()
    {
        endwin ();
    }

    void Session::update ()
    {
        char input = getch ();
        // This is only temporary
        int max_x, max_y;
        getmaxyx ( stdscr, max_y, max_x );
        std::shared_ptr < Window > window = std::make_shared < Window > ( 0, 0, max_x, max_y );

        if ( panel.get () != nullptr )
        {
            panel->update ( input, window );
        }
    }

    void Session::set_panel ( const std::shared_ptr < Panel >& panel_ )
    {
        panel = panel_;
    }

    std::shared_ptr < Panel > Session::get_panel ()
    {
        return panel;
    }
}
