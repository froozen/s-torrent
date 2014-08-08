#ifndef NCURSES_ELEMENT_GUARD
#define NCURSES_ELEMENT_GUARD

#include <memory>
#include "window.h"

namespace ncurses
{
    class Element
    {
        public:
            virtual void update ( char key, std::shared_ptr < Window > window ) = 0;

            virtual ~Element () = default;
    };
}

#endif //NCURSES_ELEMENT_GUARD
