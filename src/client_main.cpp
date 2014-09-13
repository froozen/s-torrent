#include <memory>

#include "client/event_system.h"
#include "client/client_interface.h"
#include "events/connection_receiver.h"
#include "events/hub.h"

int main( int argc, char** argv )
{
    auto connection = std::make_shared < events::Connection_receiver > ( "localhost", 31005 );
    events::Hub::get_filter ( "Send_message_event" ).subscribe ( connection );
    client::Event_system::initialize ( connection.get () );
    connection->start ();

    client::Interface::run ( connection.get () );

    std::exit ( 0 );
}
