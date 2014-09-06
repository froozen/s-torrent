#ifndef TORRENT_DISPLAY_GUARD
#define TORRENT_DISPLAY_GUARD

#include "wrappers/ncurses/element.h"
#include "wrappers/ncurses/window.h"
#include "client/torrent_data.h"

#include <memory>

namespace client
{
    class Torrent_display_element : public ncurses::Element
    {
        public:
            Torrent_display_element () = default;

            void update ( char key, std::shared_ptr < ncurses::Window > window );
            int get_prefered_width () const;
            int get_prefered_height () const;

            virtual ~Torrent_display_element () noexcept = default;
        private:
            std::string right_bound ( std::string text, size_t amount );
            void draw_progress (
                    std::shared_ptr < Torrent_data >& torrent_data,
                    std::shared_ptr < ncurses::Window > window,
                    int y
                    );

            void draw_download (
                    std::shared_ptr < Torrent_data >& torrent_data,
                    std::shared_ptr < ncurses::Window > window,
                    int y
                    );

            void draw_upload (
                    std::shared_ptr < Torrent_data >& torrent_data,
                    std::shared_ptr < ncurses::Window > window,
                    int y
                    );

            void draw_totals (
                    std::shared_ptr < std::vector < std::shared_ptr < Torrent_data > > >& torrent_data,
                    std::shared_ptr < ncurses::Window > window,
                    int y
                    );
    };
}

#endif //TORRENT_DISPLAY_GUARD
