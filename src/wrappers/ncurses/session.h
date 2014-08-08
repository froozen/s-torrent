#ifndef NCURSES_SESSION_GUARD
#define NCURSES_SESSION_GUARD

#include <memory>
#include <string>
#include <map>

#include "window.h"

namespace ncurses
{
    class Session
    {
        public:
            static std::weak_ptr < Session > get_session ();
            static void end ();

            std::weak_ptr < Window > get_window ( std::string name );
            void create_window ( std::string name, int x, int y, int width, int height );

            virtual ~Session ();

        private:
            static std::shared_ptr < Session > session_instance;
            std::map < std::string, std::shared_ptr < Window > > windows;

            Session ();
    };
}

#endif //SESSION_GUARD
