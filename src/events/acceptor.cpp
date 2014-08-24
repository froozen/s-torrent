#include "acceptor.h"
#include "wrappers/asio/client_socket.h"
#include "connection_receiver.h"
#include "hub.h"
#include "events.h"

namespace events
{
    Acceptor::Acceptor ( int port, std::string service ) :
        port ( port ),
        service ( service ),
        socket ( std::make_shared < sockets::Server_socket > ( port ) ),
        do_accept_thread ( std::thread ( &Acceptor::do_accept, this ) )
    {
        do_accept_thread.detach ();
    }

    void Acceptor::do_accept ()
    {
        while ( true )
        {
            // Accept and create Connection_receiver
            sockets::Client_socket client = socket->accept ();
            std::shared_ptr < Connection_receiver > receiver = std::make_shared < Connection_receiver > ( std::move ( client ) );

            // Make the Connection_receiver received Send_message_events
            // We want to make sure that sure filter actually exists
            Hub::get_filter ( "Send_message_event" ).subscribe ( receiver );
            receiver->start ();

            // Send event to notify others
            std::shared_ptr < Connection_accepted_event > event =
                std::make_shared < Connection_accepted_event > ( receiver.get (), port, service );
            Hub::send ( event );
        }
    }

    int Acceptor::get_port () const
    {
        return port;
    }
}
