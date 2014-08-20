#include <gtest/gtest.h>
#include <memory>
#include <functional>
#include <string>
#include "events/hub.h"
#include "events/filter_node.hpp"
#include "events/event_types/event.h"
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

        virtual ~Simple_event () = default;
};

TEST ( HubTest, simpleTest )
{
    Hub::create_filter ( "generalTest", "some_event_type" );

    std::shared_ptr < Event > received_event;
    auto save_received_event = [ & ] ( std::shared_ptr < Event > event )
    {
        received_event = event;
    };
    std::shared_ptr < Lambda_receiver < std::shared_ptr < Event > > > lambda_receiver =
        std::make_shared < Lambda_receiver < std::shared_ptr < Event > > > ( save_received_event );
    Hub::get_filter ( "generalTest" ).subscribe ( lambda_receiver );

    std::shared_ptr < Event > send_event = std::make_shared < Simple_event > ( "some_event_type" );
    Hub::send ( send_event );

    EXPECT_EQ ( send_event, received_event );
}

TEST ( HubTest, regexTest )
{
    Hub::create_filter ( "regexTest", "wild_.*_appeared" );

    std::vector < std::string > received_types;
    auto save_received_event_type = [ & ] ( std::shared_ptr < Event > event )
    {
        received_types.push_back ( event->get_type () );
    };
    std::shared_ptr < Lambda_receiver < std::shared_ptr < Event > > > lambda_receiver =
        std::make_shared < Lambda_receiver < std::shared_ptr < Event > > > ( save_received_event_type );
    Hub::get_filter ( "regexTest" ).subscribe ( lambda_receiver );

    Hub::send ( std::make_shared < Simple_event > ( "wild_dog_appeared" ) );
    Hub::send ( std::make_shared < Simple_event > ( "tame_dog_appeared" ) );
    Hub::send ( std::make_shared < Simple_event > ( "wild_cat_appeared" ) );

    EXPECT_EQ ( std::vector < std::string > ( { "wild_dog_appeared", "wild_cat_appeared" } ), received_types );
}

TEST ( HubTest, duplicateCreate )
{
    Hub::create_filter ( "doubleCreate", "first create" );
    Hub::create_filter ( "doubleCreate", "second create" );

    bool received = false;
    auto save_received_event_type = [ & ] ( std::shared_ptr < Event > event )
    {
        received = true;
    };
    std::shared_ptr < Lambda_receiver < std::shared_ptr < Event > > > lambda_receiver =
        std::make_shared < Lambda_receiver < std::shared_ptr < Event > > > ( save_received_event_type );
    Hub::get_filter ( "doubleCreate" ).subscribe ( lambda_receiver );

    Hub::send ( std::make_shared < Simple_event > ( "first create" ) );
    EXPECT_TRUE ( received );
    received = false;

    Hub::send ( std::make_shared < Simple_event > ( "second create" ) );
    EXPECT_FALSE ( received );
}
