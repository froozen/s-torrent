#include "connection_receiver.h"
#include <stdexcept>

#include "hub.h"
#include "events.h"

namespace events
{
    Connection_receiver::Connection_receiver ( std::string address, int port ) :
        connection ( std::unique_ptr < sockets::Client_socket > ( new sockets::Client_socket ( address, port ) ) ),
        connected ( true )
    {}

    Connection_receiver::Connection_receiver ( sockets::Client_socket&& socket ) :
        connection ( std::unique_ptr < sockets::Client_socket > ( new sockets::Client_socket ( std::move ( socket ) ) ) ),
        connected ( true )
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
                // Disconnect when connection is closed
                disconnect ();
            }
        }
    }

    void Connection_receiver::disconnect ()
    {
        if ( connected )
        {
            connected = false;
            std::shared_ptr < Event > event = std::make_shared < Connection_closed_event > ( this );
            Hub::send ( event );
            connection->shutdown ();
        }
    }

    void Connection_receiver::receive ( std::shared_ptr < Event > e )
    {
        // Sending is handled via events
        if ( e->get_type () == "Send_message_event" )
        {
            std::shared_ptr < Send_message_event > actual_event = std::dynamic_pointer_cast < Send_message_event > ( e );
            if ( actual_event->get_target () == this )
                connection->send ( actual_event->get_message () );
        }
    }

    Connection_receiver::~Connection_receiver ()
    {
        disconnect ();
    }
}
