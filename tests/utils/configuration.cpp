#include <gtest/gtest.h>
#include <fstream>
#include "utils/configuration.h"

class ConfigurationTest : public testing::Test
{
    public:
        ConfigurationTest () = default;

        virtual void SetUp ()
        {
            // Back old file up
            std::ifstream config_file ( "config.json" );
            old_config = std::string ( ( std::istreambuf_iterator < char > ( config_file ) ), std::istreambuf_iterator < char > () );
            config_file.close ();

            // Overwrite it with test_config
            std::ofstream create_file ( "config.json", std::ios::trunc );
            std::string test_config = "{\"int\": 123, \"double\": 0.85, \"bool\": true, \"string\": \"test_string\"}";
            create_file << test_config << std::endl;
            create_file.close ();

            // Create config
            config = utils::Configuration::get_configuration ();
        }

        void TearDown ()
        {
            // Put old file contents back
            std::ofstream create_file ( "config.json", std::ios::trunc );
            create_file << old_config << std::endl;
            create_file.close ();
        }

        virtual ~ConfigurationTest () = default;

        std::string old_config;
        std::shared_ptr < utils::Configuration > config;
};

TEST_F ( ConfigurationTest, Reading )
{
    EXPECT_EQ ( 123, config->get_int ( "int" ) );
    EXPECT_EQ ( 0.85, config->get_double ( "double" ) );
    EXPECT_EQ ( true, config->get_bool ( "bool" ) );
    EXPECT_EQ ( "test_string", config->get_string ( "string" ) );
}

TEST_F ( ConfigurationTest, FailedValues )
{
    EXPECT_EQ ( -1, config->get_int ( "string" ) );
    EXPECT_EQ ( -1, config->get_double ( "string" ) );
    EXPECT_EQ ( true, config->get_bool ( "string" ) );
}

TEST_F ( ConfigurationTest, MissingValues )
{
    EXPECT_EQ ( -1, config->get_int ( "missing" ) );
    EXPECT_EQ ( -1, config->get_double ( "missing" ) );
    EXPECT_EQ ( false, config->get_bool ( "missing" ) );
    EXPECT_EQ ( "None", config->get_string ( "missing" ) );
}

TEST_F ( ConfigurationTest, Setting )
{
    config->set_int ( "int", 321 );
    config->set_double ( "double", 1.5 );
    config->set_bool ( "bool", false );
    config->set_string ( "string", "another_string" );

    EXPECT_EQ ( 321, config->get_int ( "int" ) );
    EXPECT_EQ ( 1.5, config->get_double ( "double" ) );
    EXPECT_EQ ( false, config->get_bool ( "bool" ) );
    EXPECT_EQ ( "another_string", config->get_string ( "string" ) );
}
