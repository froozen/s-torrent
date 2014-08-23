#include "panel.h"
#include <stdexcept>

namespace ncurses
{
    Panel::Panel ( std::shared_ptr < Layout > layout ):
        layout ( layout ),
        has_border ( false ),
        prefered_width ( 0 ),
        prefered_height ( 0 )
    {}

    void Panel::update ( char key, std::shared_ptr < Window > window )
    {
        std::shared_ptr < Window > layout_window;
        if ( has_border )
        {
            // Draw the border use window without border in it for the layout
            window->draw_border ();
            window->refresh ();
            layout_window = std::make_shared < Window > (
                    window->get_x () + 1,
                    window->get_y () + 1,
                    window->get_width () - 2,
                    window->get_height () - 2
                    );
        }
        else
            layout_window = window;

        if ( layout )
            layout->update_elements ( element_vector, key, layout_window );
        else
        {
            window->draw_string ( "Error: No Layout" );
            window->refresh ();
        }
    }

    void Panel::add_element ( std::string name, const std::shared_ptr < Element >& element )
    {
        element_map.insert ( { name, element } );
        element_vector.push_back ( element );
    }

    std::shared_ptr < Element > Panel::get_element ( std::string name ) const
    {
        if ( element_map.find ( name ) != element_map.end () )
            return element_map.at ( name );
        else
            throw std::runtime_error ( "Error in ncurses::Panel::get_element : Can't find element \"" + name + "\"" );
    }
}
