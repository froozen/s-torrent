#ifndef NCURSES_LAYOUT_GUARD
#define NCURSES_LAYOUT_GUARD

#include "element.h"
#include "window.h"

#include <vector>
#include <memory>

namespace ncurses
{
    class Layout
    {
        public:
            virtual void update_elements ( std::vector < std::shared_ptr < Element > > elements,
                    char key, std::shared_ptr < Window > window ) = 0;

            virtual ~Layout () = default;
    };
}

#endif //NCURSES_LAYOUT_GUARD
