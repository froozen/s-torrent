#ifndef HORIZONTAL_STRETCH_GUARD
#define HORIZONTAL_STRETCH_GUARD

#include "layout.h"
#include "window.h"
#include "element.h"

#include <memory>
#include <vector>

namespace ncurses
{
    class Horizontal_stretch_layout : public Layout
    {
        public:
            Horizontal_stretch_layout () = default;

            void update_elements ( std::vector < std::shared_ptr < Element > > elements,
                    char key, std::shared_ptr < Window > window );

            virtual ~Horizontal_stretch_layout () = default;
    };
}

#endif //HORIZONTAL_STRETCH_GUARD
