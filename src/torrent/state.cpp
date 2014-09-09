#include "state.h"

#include <fstream>
#include <string>
#include <memory>
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

}
