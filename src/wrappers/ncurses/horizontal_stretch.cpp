#include "horizontal_stretch.h"
#include <algorithm>

namespace ncurses
{
    void Horizontal_stretch_layout::update_elements ( std::vector < std::shared_ptr < Element > > elements,
            char key, std::shared_ptr < Window > window )
    {
        int width = window->get_width () / ( ( int ) elements.size () );
        int rest = window->get_width () % ( ( int ) elements.size () );
        for ( int i = 0; i < elements.size (); i++ )
        {
            int x = window->get_x () + i * width + std::min ( i, rest );
            int y = window->get_y ();
            int win_width = width + ( i < rest ? 1 : 0 );
            int height = window->get_height ();

            std::shared_ptr < Window > element_window = std::make_shared < Window > ( x, y, win_width, height );
            elements.at ( i )->update ( key, element_window );
        }
    }
}
