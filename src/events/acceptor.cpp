#include "acceptor.h"
#include "wrappers/sockets/client_socket.h"
#include "connection_receiver.h"
#include "hub.h"
#include "events.h"

namespace events
{
    Acceptor::Acceptor ( int port, std::string service ) :
        listening ( true ),
        port ( port ),
        service ( service ),
        socket ( std::make_shared < sockets::Server_socket > ( port ) ),
        do_accept_thread ( std::thread ( &Acceptor::do_accept, this ) )
    {
        do_accept_thread.detach ();
    }

    void Acceptor::do_accept ()
    {
        while ( listening )
        {
            // Accept and create Connection_receiver
            sockets::Client_socket client = socket->next_socket ();
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
        socket->shutdown ();
    }

    int Acceptor::get_port () const
    {
        return port;
    }

    void Acceptor::stop ()
    {
        if ( listening )
        {
            listening = false;
            sockets::Client_socket s ( "localhost", port );
            s.shutdown ();
        }
    }
}
