#include "client_interface.h"

#include <memory>

#include "client/shared_data.h"
#include "events/hub.h"
#include "../events/events.h"
#include "client/events/events.h"

#include "wrappers/ncurses/session.h"
#include "client/elements/torrent_display.h"
#include "utils/json.h"

namespace client
{
    void Interface::run ( events::Connection_receiver* connection )
    {
        ncurses::Session session;
        auto torrent_display = std::make_shared < client::Torrent_display_element > ();
        session.set_root ( torrent_display );

        utils::Json_element torrent_data_request;
        torrent_data_request.set_string ( "type", "Torrent_data_requested_event" );
        events::Hub::send ( std::make_shared < events::Send_message_event > ( torrent_data_request.to_small_string (), connection ) );

        client::Shared_data::set_run ( true );
        client::Shared_data::set_connected ( true );
        while ( client::Shared_data::get_run () )
            session.update ();

        session.end ();
    }
}
