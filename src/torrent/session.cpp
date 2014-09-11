#define BOOST_ASIO_DYN_LINK

#include "session.h"
#include "state.h"
#include "utils/json.h"
#include <utility>
#include <boost/cstdint.hpp>
#include <libtorrent/ptime.hpp>

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

    std::shared_ptr < libtorrent::alert > Session::pop_alert ()
    {
        // Wait for a new alert ( 30 is realy just an arbitrary value )
        while ( !instance->session.wait_for_alert ( libtorrent::time_duration ( boost::int64_t ( 30 ) ) ) );
        return std::shared_ptr < libtorrent::alert > ( instance->session.pop_alert ().release () );
    }

    void Session::load_torrent_states ()
    {
        std::vector < std::shared_ptr < utils::Json_element > > torrent_states = State::get_torrent_states ();
        for ( auto torrent_state : torrent_states )
        {
            libtorrent::add_torrent_params p;
            if ( torrent_state->get_string ( "method" ) == "url" )
                p.url = torrent_state->get_string ( "url" );
            else if ( torrent_state->get_string ( "method" ) == "torrent_file" )
                p.ti = new libtorrent::torrent_info ( torrent_state->get_string ( "file_name" ).c_str () );
            else
                continue;
            p.save_path = torrent_state->get_string ( "save_path" );
            libtorrent::torrent_handle torrent = instance->session.add_torrent ( p );
            torrent.set_download_limit ( 300000 );
        }
    }
}
