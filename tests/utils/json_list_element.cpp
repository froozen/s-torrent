#include <gtest/gtest.h>
#include <fstream>
#include "utils/configuration.h"
#include <iostream>

class JsonListElementTest : public testing::Test
{
    public:
        JsonListElementTest () = default;

        virtual void SetUp ()
        {
            // Back old file up
            std::ifstream config_file ( "config.json" );
            old_config = std::string ( ( std::istreambuf_iterator < char > ( config_file ) ), std::istreambuf_iterator < char > () );
            config_file.close ();

            // Overwrite it with test_config
            std::ofstream create_file ( "config.json", std::ios::trunc );
            std::string test_config = "{\"list\": [ 123, 0.85, true, \"test_string\", { \"value\": 1 } ]}";
            create_file << test_config << std::endl;
            create_file.close ();

            // Create config
            utils::Configuration::load ( "config.json" );
            config = utils::Configuration::get_root ()->get_list_element ( "list" );
        }

        void TearDown ()
        {
            // Put old file contents back
            std::ofstream create_file ( "config.json", std::ios::trunc );
            create_file << old_config;
            create_file.close ();
        }

        virtual ~JsonListElementTest () = default;

        std::string old_config;
        std::shared_ptr < utils::Json_list_element > config;
};

TEST_F ( JsonListElementTest, ReadingTest )
{
    EXPECT_EQ ( 123, config->get_int ( 0 ) );
    EXPECT_EQ ( 0.85, config->get_double ( 1 ) );
    EXPECT_EQ ( true, config->get_bool ( 2 ) );
    EXPECT_EQ ( "test_string", config->get_string ( 3 ) );

    std::shared_ptr < utils::Json_element > sub_element = config->get_element ( 4 );
    EXPECT_EQ ( 1, sub_element->get_int ( "value" ) );
}

TEST_F ( JsonListElementTest, FailedValuesTest )
{
    EXPECT_EQ ( -1, config->get_int ( 3 ) );
    EXPECT_EQ ( -1, config->get_double ( 3 ) );
    EXPECT_EQ ( false, config->get_bool ( 3 ) );
}

TEST_F ( JsonListElementTest, MissingValuesTest )
{
    EXPECT_EQ ( -1, config->get_int ( 5 ) );
    EXPECT_EQ ( -1, config->get_double ( 5 ) );
    EXPECT_EQ ( false, config->get_bool ( 5 ) );
    EXPECT_EQ ( "None", config->get_string ( 5 ) );
}

TEST_F ( JsonListElementTest, CreatingNewValuesTest )
{
    config->set_int ( 5, 13 );
    config->set_double ( 6, 3.14 );
    config->set_bool ( 7, true );
    config->set_string ( 8, "a new string" );

    EXPECT_EQ ( 13, config->get_int ( 5 ) );
    EXPECT_EQ ( 3.14, config->get_double ( 6 ) );
    EXPECT_EQ ( true, config->get_bool ( 7 ) );
    EXPECT_EQ ( "a new string", config->get_string ( 8 ) );
}

TEST_F ( JsonListElementTest, SettingTest )
{
    config->set_int ( 0, 321 );
    config->set_double ( 1, 1.5 );
    config->set_bool ( 2, false );
    config->set_string ( 3, "another_string" );

    utils::Json_element element;
    element.set_int ( "value", 2 );
    config->set_element ( 4, element );

    EXPECT_EQ ( 321, config->get_int ( 0 ) );
    EXPECT_EQ ( 1.5, config->get_double ( 1 ) );
    EXPECT_EQ ( false, config->get_bool ( 2 ) );
    EXPECT_EQ ( "another_string", config->get_string ( 3 ) );

    std::shared_ptr < utils::Json_element > test_element = config->get_element ( 4 );
    EXPECT_EQ  ( 2, test_element->get_int ( "value" ) );
}

TEST_F ( JsonListElementTest, DeathTest )
{
    EXPECT_THROW ( config->get_element ( 0 ), std::runtime_error );
    EXPECT_THROW ( config->get_list_element ( 0 ), std::runtime_error );

    // Create it from something other than an array
    Json::Value not_an_array;
    not_an_array = 1;
    Json::Value* ptr = &not_an_array;
    EXPECT_THROW ( utils::Json_element c = utils::Json_element ( ptr ), std::runtime_error );
}
