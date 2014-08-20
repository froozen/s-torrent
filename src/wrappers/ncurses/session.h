#ifndef NCURSES_SESSION_GUARD
#define NCURSES_SESSION_GUARD

#include <memory>
#include <string>
#include <map>

#include "window.h"
#include "panel.h"

namespace ncurses
{
    // Session is a Singleton
    class Session
    {
        public:
            static std::weak_ptr < Session > get_session ();
            // Destroys current Session
            static void end ();

            std::weak_ptr < Element > get_element ( std::string name );
            // Session needs a root panel to work
            void set_panel ( const std::shared_ptr < Panel >& panel );
            std::shared_ptr < Panel > get_panel () const;
            void update ();

            virtual ~Session ();

        private:
            static std::shared_ptr < Session > session_instance;
            std::shared_ptr < Panel > panel;

            Session ();
    };
}

#endif //SESSION_GUARD
