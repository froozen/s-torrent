#include "element_stack.h"

#include <string>

namespace ncurses
{
    void Element_stack::update ( char key, std::shared_ptr < Window > window )
    {
        if ( !elements.empty () )
            elements.top ()->update ( key, window );
        else
        {
            std::string message = "No elements in stack";
            if ( static_cast < unsigned int > ( window->get_width () ) >= message.size () )
            {
                window->set_fg_color ( Window::RED );
                window->move ( 0, 0 );
                window->draw_string ( message );
                window->refresh ();
            }
        }
    }

    int Element_stack::get_prefered_height () const
    {
        if ( !elements.empty () )
            return elements.top ()->get_prefered_height ();

        return 0;
    }

    int Element_stack::get_prefered_width () const
    {
        if ( !elements.empty () )
            return elements.top ()->get_prefered_width ();

        return 0;
    }

    void Element_stack::push ( const std::shared_ptr < Element >& element )
    {
        elements.push ( element );
    }

    void Element_stack::pop ()
    {
        elements.pop ();
    }
}
