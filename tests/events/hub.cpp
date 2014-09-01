#include <gtest/gtest.h>
#include <memory>
#include <functional>
#include <string>
#include <chrono>
#include <thread>

#include "events/hub.h"
#include "events/filter_node.hpp"
#include "events/events.h"
#include "events/lambda_receiver.hpp"

using namespace events;

class Simple_event : public Event
{
    public:
        Simple_event ( std::string type ) :
            type ( type )
        {}

        std::string get_type () { return type; };
        std::string type;

        virtual ~Simple_event () noexcept = default;
};

TEST ( HubTest, SimpleTest )
{
    std::shared_ptr < Event > received_event;
    auto save_received_event = [ & ] ( std::shared_ptr < Event > event )
    {
        received_event = event;
    };
    std::shared_ptr < Lambda_receiver < std::shared_ptr < Event > > > lambda_receiver =
        std::make_shared < Lambda_receiver < std::shared_ptr < Event > > > ( save_received_event );
    Hub::get_filter ( "some_event_type" ).subscribe ( lambda_receiver );

    std::shared_ptr < Event > send_event = std::make_shared < Simple_event > ( "some_event_type" );
    Hub::send ( send_event );

    std::this_thread::sleep_for ( std::chrono::milliseconds ( 50 ) );

    EXPECT_EQ ( send_event, received_event );
}

TEST ( HubTest, RegexTest )
{
    std::vector < std::string > received_types;
    auto save_received_event_type = [ & ] ( std::shared_ptr < Event > event )
    {
        received_types.push_back ( event->get_type () );
    };
    std::shared_ptr < Lambda_receiver < std::shared_ptr < Event > > > lambda_receiver =
        std::make_shared < Lambda_receiver < std::shared_ptr < Event > > > ( save_received_event_type );
    Hub::get_filter ( "wild_.*_appeared" ).subscribe ( lambda_receiver );

    Hub::send ( std::make_shared < Simple_event > ( "wild_dog_appeared" ) );
    Hub::send ( std::make_shared < Simple_event > ( "tame_dog_appeared" ) );
    Hub::send ( std::make_shared < Simple_event > ( "wild_cat_appeared" ) );

    EXPECT_EQ ( std::vector < std::string > ( { "wild_dog_appeared", "wild_cat_appeared" } ), received_types );
}
