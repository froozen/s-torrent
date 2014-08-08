#ifndef NCURSES_SESSION_GUARD
#define NCURSES_SESSION_GUARD

#include <memory>
#include <string>
#include <map>

#include "window.h"
#include "element.h"

namespace ncurses
{
    class Session
    {
        public:
            static std::weak_ptr < Session > get_session ();
            static void end ();

            std::weak_ptr < Element > get_element ( std::string name );
            void add_element ( std::string name, std::shared_ptr < Element > element );
            void update ();

            virtual ~Session ();

        private:
            static std::shared_ptr < Session > session_instance;
            std::map < std::string, std::shared_ptr < Element > > elements;

            Session ();
    };
}

#endif //SESSION_GUARD
