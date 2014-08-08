#include "window.h"

#include <stdexcept>

namespace ncurses
{
    Window::Window ( WINDOW* window ):
        window ( window )
    {}

    Window::Window ( int x, int y, int width, int height )
    {
        window = newwin ( height, width, y, x );
        wrefresh ( window );
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
        wrefresh ( window );
    }

    void Window::add_character ( char c )
    {
        waddch ( window, c );
        wrefresh ( window );
    }

    void Window::set_color ( int fg, int bg )
    {
        if ( fg > 7 || bg > 7 || fg < -1 || bg < -1 )
            throw std::runtime_error ( "ncurses::Window::set_color: Bad arguments! fg or bg out of range [ -1 | 7 ]" );

        wattron ( window, COLOR_PAIR ( 2 + fg + 8 * ( 1 + bg ) ) );
    }
}
