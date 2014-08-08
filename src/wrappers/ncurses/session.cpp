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

    std::weak_ptr < Window > Session::get_window ( std::string name )
    {
        return std::weak_ptr < Window > ( windows.at ( name ) );
    }

    void Session::create_window ( std::string name, int x, int y, int width, int height )
    {
        std::shared_ptr < Window > new_window = std::make_shared < Window > ( x, y, width, height );
        windows.insert ( { name, new_window } );
    }
}
