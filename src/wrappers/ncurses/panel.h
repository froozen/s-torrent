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
            void set_border ( bool border ) { this->border = border; }
            void set_prefered_width ( int prefered_width ) { this->prefered_width = prefered_width; }
            void set_prefered_height ( int prefered_height ) { this->prefered_height = prefered_height; }

            int get_prefered_width () const { return prefered_width; }
            int get_prefered_height () const { return prefered_height; }

            void add_element ( std::string name, const std::shared_ptr < Element >& element );
            std::shared_ptr < Element > get_element ( std::string name ) const;

            virtual ~Panel () = default;

        private:
            std::shared_ptr < Layout > layout;
            std::vector < std::shared_ptr < Element > > element_vector;
            std::map < std::string, std::shared_ptr < Element > > element_map;
            bool border;
            int prefered_width, prefered_height;
    };
}

#endif //NCURSES_PANEL_GUARD
