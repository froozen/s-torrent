#include "add_torrent_event.h"

#include "utils/json.h"
#include "utils/base64.h"
#include <fstream>

namespace client
{
    Add_torrent_event::Add_torrent_event ( Method method, std::string source ) :
        method ( method ),
        source ( source )
    {}

    std::string Add_torrent_event::get_network_signal ()
    {
        if ( method == Method::URL )
        {
            utils::Json_element signal;
            signal.set_string ( "type", "Add_torrent_event" );
            signal.set_string ( "method", "url" );
            signal.set_string ( "url", source );
            return  signal.to_small_string ();
        }

        else if ( method == Method::FILE )
        {
            std::ifstream torrent_file ( source.c_str (), std::ios_base::binary );
            if ( torrent_file.is_open () )
            {
                std::string content ( ( std::istreambuf_iterator < char > ( torrent_file ) ), std::istreambuf_iterator < char > () );
                content = utils::base64_encode ( reinterpret_cast < const unsigned char* > ( content.c_str () ), content.length () );

                utils::Json_element signal;
                signal.set_string ( "type", "Add_torrent_event" );
                signal.set_string ( "method", "file" );
                signal.set_string ( "file_name", "_" + source );
                signal.set_string ( "content", content );
                return signal.to_small_string ();
            }
        }

        return "";
    }
}
