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
            Session ();
            Session ( const std::shared_ptr < Element >& root );

            // Session needs a root panel to work
            void set_root ( const std::shared_ptr < Element >& root );
            std::shared_ptr < Element > get_root ();
            void update ();
            void end ();

            virtual ~Session ();

        private:
            static bool created;
            std::shared_ptr < Window > window;
            std::shared_ptr < Element > root;
    };
}

#endif //SESSION_GUARD
