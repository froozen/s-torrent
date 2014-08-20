#include "connection_receiver.h"
#include <stdexcept>

#include "hub.h"
#include "event_types/read_line_event.h"
#include "event_types/connection_closed_event.h"
#include "event_types/send_message_event.h"

namespace events
{
    Connection_receiver::Connection_receiver ( std::string address, std::string service ) :
        connection ( std::unique_ptr < sockets::Client_socket > ( new sockets::Client_socket ( address, service ) ) ),
        connected ( true )
    {}

    Connection_receiver::Connection_receiver ( std::string address, int port ) :
        Connection_receiver ( address, std::to_string ( port ) )
    {}

    void Connection_receiver::start ()
    {
        listening_thread = std::thread ( std::thread ( &Connection_receiver::listen_on_socket, this ) );
        listening_thread.detach ();
    }

    void Connection_receiver::listen_on_socket ()
    {
        while ( connected )
        {
            try
            {
                std::string next_line = connection->read_line ();
                std::shared_ptr < Event > event = std::make_shared < Read_line_event > ( next_line, this );
                Hub::send ( event );
            }
            catch ( std::runtime_error& e )
            {
                disconnect ();
            }
        }
    }

    void Connection_receiver::disconnect ()
    {
        if ( connected )
        {
            std::shared_ptr < Event > event = std::make_shared < Connection_closed_event > ( this );
            Hub::send ( event );
            connection->close ();
            connected = false;
        }
    }

    void Connection_receiver::receive ( std::shared_ptr < Event > e )
    {
        if ( e->get_type () == "Send_message_event" )
        {
            std::shared_ptr < Send_message_event > actual_event = std::dynamic_pointer_cast < Send_message_event > ( e );
            connection->send ( actual_event->get_message () );
        }
    }
}
