#ifndef TORRENT_SESSION_GUARD
#define TORRENT_SESSION_GUARD

#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>

#include <vector>
#include <memory>

namespace torrent
{
    class Session
    {
        public:
            static void initialize ();
            static void load_torrent_states ();

            static std::vector < libtorrent::torrent_handle > get_torrents ();
            static libtorrent::torrent_handle add_torrent ( libtorrent::add_torrent_params const& params );
            static std::shared_ptr < libtorrent::alert > pop_alert ();

        private:
            Session ();

            static std::unique_ptr < Session > instance;
            libtorrent::session session;
    };
}

#endif //TORRENT_SESSION_GUARD
