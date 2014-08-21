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
    {}


    void Acceptor::do_accept ()
    {
        while ( true )
        {
            sockets::Client_socket client = socket->accept ();
            std::shared_ptr < Connection_receiver > receiver = std::make_shared < Connection_receiver > ( std::move ( client ) );

            // We want to make sure that our filter actually exists
            Hub::create_filter ( "send_message", "Send_message_event" );
            Hub::get_filter ( "send_message" ).subscribe ( receiver );
            receiver->start ();
            std::shared_ptr < Connection_accepted_event > event =
                std::make_shared < Connection_accepted_event > ( receiver.get (), port, service );
            Hub::send ( event );
        }
    }
}
