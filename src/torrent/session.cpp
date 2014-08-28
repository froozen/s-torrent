#define BOOST_ASIO_DYN_LINK

#include "session.h"
#include <utility>

namespace torrent
{
    std::unique_ptr < Session > Session::instance;

    Session::Session () :
        session (
            libtorrent::fingerprint ( "LT", LIBTORRENT_VERSION_MAJOR, LIBTORRENT_VERSION_MINOR, 0, 0 ),
            std::make_pair ( 6881, 6889 )
            )
    {}

    void Session::initialize ()
    {
        instance.reset ( new Session );
    }

    std::vector < libtorrent::torrent_handle > Session::get_torrents ()
    {
        return instance->session.get_torrents ();
    }

    libtorrent::torrent_handle Session::add_torrent ( libtorrent::add_torrent_params const& params )
    {
        return instance->session.add_torrent ( params );
    }
}
