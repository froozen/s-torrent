#ifndef NCURSES_SESSION_GUARD
#define NCURSES_SESSION_GUARD

#include <memory>
#include <string>
#include <map>

#include "window.h"
#include "panel.h"

namespace ncurses
{
    class Session
    {
        public:
            static void init ();
            static void end ();

            // Session needs a root panel to work
            static void set_panel ( const std::shared_ptr < Panel >& panel );
            static std::shared_ptr < Panel > get_panel ();
            static void update ();

        private:
            static std::shared_ptr < Panel > panel;

            Session ();
    };
}

#endif //SESSION_GUARD
