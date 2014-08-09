#include "window.h"

#include <stdexcept>

namespace ncurses
{
    Window::Window ( WINDOW* window ):
        window ( window )
    {
        getmaxyx ( window, height, width );
        getbegyx ( window, y, x );
    }

    Window::Window ( int x, int y, int width, int height ):
        height ( height ),
        width ( width ),
        x ( x ), y ( y )
    {
        window = newwin ( height, width, y, x );
    }

    Window::~Window ()
    {
        werase ( window );
        delwin ( window );
    }

    void Window::move ( int x, int y )
    {
        wmove ( window, y, x );
    }

    void Window::print_string ( std::string s )
    {
        waddstr ( window, s.c_str () );
    }

    void Window::add_character ( char c )
    {
        waddch ( window, c );
    }

    void Window::set_color ( int fg, int bg )
    {
        if ( fg > 7 || bg > 7 || fg < -1 || bg < -1 )
            throw std::runtime_error ( "ncurses::Window::set_color: Bad arguments! fg or bg out of range [ -1 | 7 ]" );

        wattron ( window, COLOR_PAIR ( 2 + fg + 8 * ( 1 + bg ) ) );
    }

    void Window::draw_border ()
    {
        box ( window, 0, 0 );
    }

    void Window::refresh ()
    {
        wrefresh ( window );
    }
}
