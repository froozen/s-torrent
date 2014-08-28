#include <memory>

#include "wrappers/ncurses/session.h"
#include "wrappers/ncurses/panel.h"
#include "wrappers/ncurses/stretch.h"
#include "wrappers/ncurses/orientation.h"
#include "wrappers/ncurses/element_stack.h"

int main()
{
    ncurses::Session::init ();

    std::shared_ptr < ncurses::Orientation > orientation = std::make_shared < ncurses::Horizontal > ();
    std::shared_ptr < ncurses::Stretch_layout > layout = std::make_shared < ncurses::Stretch_layout > ();
    layout->set_orientation ( orientation );
    std::shared_ptr < ncurses::Panel > panel = std::make_shared < ncurses::Panel > ( layout );
    std::shared_ptr < ncurses::Element > stack = std::make_shared < ncurses::Element_stack > ();
    panel->add_element ( "stack", stack );
    ncurses::Session::set_panel ( panel );

    while ( true )
        ncurses::Session::update ();

    ncurses::Session::end ();
    return 0;
}
