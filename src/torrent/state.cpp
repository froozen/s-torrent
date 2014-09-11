#include "state.h"

#include <fstream>
#include <string>
#include <stdexcept>

namespace torrent
{
    utils::Json_element State::state;

    void State::load ()
    {
        std::ifstream state_file ( ".s-torrent-state" );
        if ( state_file.is_open () )
        {
            std::string content ( ( std::istreambuf_iterator < char > ( state_file ) ), std::istreambuf_iterator < char > () );

            try { state = utils::Json_element ( content ); }
            catch ( std::runtime_error& e ) { throw std::runtime_error ( "Error in torrent::state::load : Parsing failed :\n" + content ); }
        }
    }

    void State::save ()
    {
        std::ofstream state_file ( ".s-torrent-state" );
        state_file << state.to_small_string ();
    }

    std::vector < std::shared_ptr < utils::Json_element > > State::get_torrent_states ()
    {
        std::vector < std::shared_ptr < utils::Json_element > > torrent_states;
        try
        {
            std::shared_ptr < utils::Json_list_element > torrent_states_json = state.get_list_element ( "torrent_states" );
            for ( int i = 0; i < torrent_states_json->size (); i++ )
                torrent_states.push_back ( torrent_states_json->get_element ( i ) );
        }
        catch ( std::runtime_error& e )
        {}

        return torrent_states;
    }

    void State::add_torrent_state ( const utils::Json_element& torrent_state )
    {
        std::shared_ptr < utils::Json_list_element > torrent_stats_json = state.get_list_element ( "torrent_states" );
        torrent_stats_json->append_element ( torrent_state );
        save ();
    }
}
