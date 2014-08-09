#include "panel.h"

namespace ncurses
{
    Panel::Panel ( std::shared_ptr < Layout > layout ):
        layout ( layout )
    {}

    void Panel::update ( char key, std::shared_ptr < Window > window )
    {
        if ( layout )
            layout->update_elements ( element_vector, key, window );
    }

    void Panel::add_element ( std::string name, std::shared_ptr < Element > element )
    {
        element_map.insert ( { name, element } );
        element_vector.push_back ( element );
    }

    std::shared_ptr < Element > Panel::get_element ( std::string name )
    {
        return element_map.at ( name );
    }
}
