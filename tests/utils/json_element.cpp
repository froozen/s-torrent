#include <gtest/gtest.h>
#include <fstream>
#include "utils/configuration.h"

class JsonElementTest : public testing::Test
{
    public:
        JsonElementTest () = default;

        virtual void SetUp ()
        {
            // Back old file up
            std::ifstream config_file ( "config.json" );
            old_config = std::string ( ( std::istreambuf_iterator < char > ( config_file ) ), std::istreambuf_iterator < char > () );
            config_file.close ();

            // Overwrite it with test_config
            std::ofstream create_file ( "config.json", std::ios::trunc );
            std::string test_config = "{\"int\": 123, \"double\": 0.85, \"bool\": true, \"string\": \"test_string\", \"element\": { \"value\": 1 } }";
            create_file << test_config << std::endl;
            create_file.close ();

            // Create config
            utils::Configuration::load ( "config.json" );
            config = utils::Configuration::get_root ();
        }

        void TearDown ()
        {
            // Put old file contents back
            std::ofstream create_file ( "config.json", std::ios::trunc );
            create_file << old_config;
            create_file.close ();
        }

        virtual ~JsonElementTest () = default;

        std::string old_config;
        std::shared_ptr < utils::Json_element > config;
};

TEST_F ( JsonElementTest, ReadingTest )
{
    EXPECT_EQ ( 123, config->get_int ( "int" ) );
    EXPECT_EQ ( 0.85, config->get_double ( "double" ) );
    EXPECT_EQ ( true, config->get_bool ( "bool" ) );
    EXPECT_EQ ( "test_string", config->get_string ( "string" ) );

    std::shared_ptr < utils::Json_element > sub_element = config->get_element ( "element" );
    EXPECT_EQ ( 1, sub_element->get_int ( "value" ) );
}

TEST_F ( JsonElementTest, FailedValuesTest )
{
    EXPECT_EQ ( -1, config->get_int ( "string" ) );
    EXPECT_EQ ( -1, config->get_double ( "string" ) );
    EXPECT_EQ ( false, config->get_bool ( "string" ) );
}

TEST_F ( JsonElementTest, MissingValuesTest )
{
    EXPECT_EQ ( -1, config->get_int ( "missing" ) );
    EXPECT_EQ ( -1, config->get_double ( "missing" ) );
    EXPECT_EQ ( false, config->get_bool ( "missing" ) );
    EXPECT_EQ ( "None", config->get_string ( "missing" ) );
}

TEST_F ( JsonElementTest, CreatingNewValuesTest )
{
    config->set_int ( "new_int", 13 );
    config->set_double ( "new_double", 3.14 );
    config->set_bool ( "new_bool", true );
    config->set_string ( "new_string", "a new string" );

    EXPECT_EQ ( 13, config->get_int ( "new_int" ) );
    EXPECT_EQ ( 3.14, config->get_double ( "new_double" ) );
    EXPECT_EQ ( true, config->get_bool ( "new_bool" ) );
    EXPECT_EQ ( "a new string", config->get_string ( "new_string" ) );
}

TEST_F ( JsonElementTest, SettingTest )
{
    config->set_int ( "int", 321 );
    config->set_double ( "double", 1.5 );
    config->set_bool ( "bool", false );
    config->set_string ( "string", "another_string" );

    utils::Json_element element;
    element.set_int ( "value", 2 );
    config->set_element ( "element", element );

    EXPECT_EQ ( 321, config->get_int ( "int" ) );
    EXPECT_EQ ( 1.5, config->get_double ( "double" ) );
    EXPECT_EQ ( false, config->get_bool ( "bool" ) );
    EXPECT_EQ ( "another_string", config->get_string ( "string" ) );

    std::shared_ptr < utils::Json_element > test_element = config->get_element ( "element" );
    EXPECT_EQ  ( 2, test_element->get_int ( "value" ) );
}

TEST_F ( JsonElementTest, DeathTest )
{
    EXPECT_THROW ( config->get_element ( "int" ), std::runtime_error );
    EXPECT_THROW ( config->get_list_element ( "int" ), std::runtime_error );

    // Create it from something other than an object
    Json::Value not_an_object;
    not_an_object = 1;
    Json::Value* ptr = &not_an_object;
    EXPECT_THROW ( utils::Json_element c = utils::Json_element ( ptr ), std::runtime_error );
}
