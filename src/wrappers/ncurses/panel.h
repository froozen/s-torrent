#ifndef NCURSES_PANEL_GUARD
#define NCURSES_PANEL_GUARD

#include "element.h"
#include "layout.h"
#include "window.h"

#include <memory>
#include <vector>
#include <string>
#include <map>

namespace ncurses
{
    class Panel : public Element
    {
        public:
            Panel () = default;
            Panel ( std::shared_ptr < Layout > layout );

            void update ( char key, std::shared_ptr < Window > );
            int get_prefered_width () { return 0; }
            int get_prefered_height () { return 0; }

            void add_element ( std::string name, std::shared_ptr < Element > element );
            std::shared_ptr < Element > get_element ( std::string name );

            virtual ~Panel () = default;

        private:
            std::shared_ptr < Layout > layout;
            std::vector < std::shared_ptr < Element > > element_vector;
            std::map < std::string, std::shared_ptr < Element > > element_map;
    };
}

#endif //NCURSES_PANEL_GUARD
