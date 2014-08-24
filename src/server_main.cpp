#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "events/acceptor_hub.h"
#include "events/hub.h"
#include "events/events.h"
#include "events/lambda_receiver.hpp"

#include "utils/json_element.h"

void on_receive ( std::shared_ptr < events::Event > event )
{
    auto read_line_event = std::dynamic_pointer_cast < events::Read_line_event > ( event );
    try
    {
        utils::Json_element received_json ( read_line_event->get_line () );
        std::string name = received_json.get_string ( "name" );
        if ( name != "None" )
        {
            utils::Json_element response;
            response.set_string ( "answer", "Hello there, " + name + "." );
            auto response_event = std::make_shared < events::Send_message_event > ( response.to_small_string (), read_line_event->get_origin () );
            events::Hub::send ( response_event );
        }
    }
    catch ( std::runtime_error& e )
    {}
}
void setup ()
{
    auto on_receive_receiver = std::make_shared < events::Lambda_receiver < std::shared_ptr < events::Event > > > ( &on_receive );
    events::Hub::get_filter ( "Read_line_event" ).subscribe ( on_receive_receiver );
    events::Acceptor_hub::accept ( 31005, "listening port" );
}

int main ()
{
    setup ();

    while ( true )
        std::this_thread::sleep_for ( std::chrono::seconds ( 5 ) );

    std::cout << "Server!" << std::endl;
    return 0;
}
