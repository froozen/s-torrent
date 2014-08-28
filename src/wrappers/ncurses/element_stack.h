#ifndef ELEMENT_STACK_GUARD
#define ELEMENT_STACK_GUARD

#include "element.h"
#include "window.h"

#include <stack>
#include <memory>

namespace ncurses
{
    class Element_stack : public Element
    {
        public:
            Element_stack () = default;

            void update ( char key, std::shared_ptr < Window > window );
            int get_prefered_width () const;
            int get_prefered_height () const;

            void push ( const std::shared_ptr < Element >& element );
            void pop ();

            virtual ~Element_stack () = default;

        private:
            std::stack < std::shared_ptr < Element > > elements;
    };
}

#endif //ELEMENT_STACK_GUARD
