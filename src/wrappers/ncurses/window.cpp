#include "window.h"

#include <stdexcept>

namespace ncurses
{
    Window::Window ( WINDOW* window ):
        window ( window ),
        fg_color ( -1 ),
        bg_color ( -1 )
    {
        getmaxyx ( window, height, width );
        getbegyx ( window, y, x );
    }

    Window::Window ( int x, int y, int width, int height ):
        height ( height ),
        width ( width ),
        x ( x ), y ( y ),
        fg_color ( -1 ),
        bg_color ( -1 )
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
        set_fg_color ( fg );
        set_bg_color ( bg );
    }

    void Window::set_fg_color ( int fg_color )
    {
        if ( fg_color > -2 && fg_color < 8 )
        {
            this->fg_color = fg_color;
            wattron ( window, COLOR_PAIR ( get_color_id () ) );
        }
        else
            throw std::runtime_error ( "ncurses::Window::set_fg_color: Bad Argument! fg_color out of range [ -1 | 7 ]" );
    }

    void Window::set_bg_color ( int bg_color )
    {
        if ( bg_color > -2 && bg_color < 8 )
        {
            this->bg_color = bg_color;
            wattron ( window, COLOR_PAIR ( get_color_id () ) );
        }
        else
            throw std::runtime_error ( "ncurses::Window::set_bg_color: Bad Argument! bg_color out of range [ -1 | 7 ]" );
    }

    int Window::get_color_id () const
    {
        return 2 + fg_color + 8 * ( 1 + bg_color );
    }

    void Window::set_color ( int color_id )
    {
       if ( color_id > 74 || color_id < 1 )
           throw std::runtime_error ( "ncurses::Window::set_color: Bad argument! color_id > 73" );

       fg_color = ( color_id - 2 ) % 8;
       bg_color = ( ( ( color_id - 2 ) - fg_color ) ) / 8 - 1;
       wattron ( window, COLOR_PAIR ( color_id ) );
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
