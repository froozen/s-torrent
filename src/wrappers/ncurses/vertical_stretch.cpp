#include "vertical_stretch.h"
#include <algorithm>

namespace ncurses
{
    void Vertical_stretch_layout::update_elements ( std::vector < std::shared_ptr < Element > > elements,
            char key, std::shared_ptr < Window > window )
    {
        int height = window->get_height () / ( ( int ) elements.size () );
        int rest = window->get_height () % ( ( int ) elements.size () );
        for ( int i = 0; i < elements.size (); i++ )
        {
            int x = window->get_x ();
            int y = window->get_y () + height * i + std::min ( i, rest );
            int width = window->get_width ();
            int win_height = height + ( i < rest ? 1 : 0 );

            std::shared_ptr < Window > element_window = std::make_shared < Window > ( x, y, width, win_height );
            elements.at ( i )->update ( key, element_window );
        }
    }
}
