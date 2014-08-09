#include "session.h"

#include <ncurses.h>

namespace ncurses
{
    std::shared_ptr < Session > Session::session_instance;

    Session::Session ()
    {
        initscr ();
        cbreak ();
        noecho ();
        start_color ();
        use_default_colors ();
        refresh ();

        // Init all possible color pairs, to enable
        // Window::set_color
        for ( int fg = -1; fg < 8; fg++ )
        {
            for ( int bg = -1; bg < 8; bg++ )
            {
                init_pair ( 2 + fg + 8 * ( 1 + bg ), fg, bg );
            }
        }
    }

    Session::~Session ()
    {
        if ( session_instance.get () != nullptr )
            endwin ();
    }

    std::weak_ptr < Session > Session::get_session ()
    {
        if ( session_instance.get () == nullptr )
            session_instance = std::shared_ptr < Session > ( new Session () );

        return std::weak_ptr < Session > ( session_instance );
    }

    void Session::end ()
    {
        if ( session_instance.get () != nullptr )
        {
            endwin ();
            session_instance.reset ();
        }
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

    void Session::set_panel ( std::shared_ptr < Panel > panel )
    {
        this->panel = panel;
    }

    std::shared_ptr < Panel > Session::get_panel () const
    {
        return this->panel;
    }
}
