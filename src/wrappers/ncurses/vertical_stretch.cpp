#include "vertical_stretch.h"

namespace ncurses
{
    void Vertical_stretch_layout::update_elements ( std::vector < std::shared_ptr < Element > > elements,
            char key, std::shared_ptr < Window > window )
    {
        int height = window->get_height () / ( ( int ) elements.size () );
        for ( int i = 0; i < elements.size (); i++ )
        {
            std::shared_ptr < Window > element_window = std::make_shared < Window >
                ( window->get_x (), window->get_y () + height * i, window->get_width (), height );
            elements.at ( i )->update ( key, element_window );
        }
    }
}
