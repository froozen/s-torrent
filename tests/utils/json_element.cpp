#include <gtest/gtest.h>
#include <fstream>
#include "utils/json.h"

class JsonElementTest : public testing::Test
{
    public:
        JsonElementTest () = default;

        virtual void SetUp ()
        {

            std::string json_string = "{\"int\": 123, \"double\": 0.85, \"bool\": true, \"string\": \"test_string\", \"element\": { \"value\": 1 } }";
            json_element = std::make_shared < utils::Json_element > ( json_string );
        }

        virtual ~JsonElementTest () = default;

        std::shared_ptr < utils::Json_element > json_element;
};

TEST_F ( JsonElementTest, ReadingTest )
{
    EXPECT_EQ ( 123, json_element->get_int ( "int" ) );
    EXPECT_EQ ( 0.85, json_element->get_double ( "double" ) );
    EXPECT_EQ ( true, json_element->get_bool ( "bool" ) );
    EXPECT_EQ ( "test_string", json_element->get_string ( "string" ) );

    std::shared_ptr < utils::Json_element > sub_element = json_element->get_element ( "element" );
    EXPECT_EQ ( 1, sub_element->get_int ( "value" ) );
}

TEST_F ( JsonElementTest, FailedValuesTest )
{
    EXPECT_EQ ( -1, json_element->get_int ( "string" ) );
    EXPECT_EQ ( -1, json_element->get_double ( "string" ) );
    EXPECT_EQ ( false, json_element->get_bool ( "string" ) );
}

TEST_F ( JsonElementTest, MissingValuesTest )
{
    EXPECT_EQ ( -1, json_element->get_int ( "missing" ) );
    EXPECT_EQ ( -1, json_element->get_double ( "missing" ) );
    EXPECT_EQ ( false, json_element->get_bool ( "missing" ) );
    EXPECT_EQ ( "None", json_element->get_string ( "missing" ) );
}

TEST_F ( JsonElementTest, CreatingNewValuesTest )
{
    json_element->set_int ( "new_int", 13 );
    json_element->set_double ( "new_double", 3.14 );
    json_element->set_bool ( "new_bool", true );
    json_element->set_string ( "new_string", "a new string" );

    EXPECT_EQ ( 13, json_element->get_int ( "new_int" ) );
    EXPECT_EQ ( 3.14, json_element->get_double ( "new_double" ) );
    EXPECT_EQ ( true, json_element->get_bool ( "new_bool" ) );
    EXPECT_EQ ( "a new string", json_element->get_string ( "new_string" ) );
}

TEST_F ( JsonElementTest, SettingTest )
{
    json_element->set_int ( "int", 321 );
    json_element->set_double ( "double", 1.5 );
    json_element->set_bool ( "bool", false );
    json_element->set_string ( "string", "another_string" );

    utils::Json_element element;
    element.set_int ( "value", 2 );
    json_element->set_element ( "element", element );

    EXPECT_EQ ( 321, json_element->get_int ( "int" ) );
    EXPECT_EQ ( 1.5, json_element->get_double ( "double" ) );
    EXPECT_EQ ( false, json_element->get_bool ( "bool" ) );
    EXPECT_EQ ( "another_string", json_element->get_string ( "string" ) );

    std::shared_ptr < utils::Json_element > test_element = json_element->get_element ( "element" );
    EXPECT_EQ  ( 2, test_element->get_int ( "value" ) );
}

TEST_F ( JsonElementTest, DeathTest )
{
    EXPECT_THROW ( json_element->get_element ( "int" ), std::runtime_error );
    EXPECT_THROW ( json_element->get_list_element ( "int" ), std::runtime_error );

    // Create it from something other than an object
    Json::Value not_an_object;
    not_an_object = 1;
    Json::Value* ptr = &not_an_object;
    EXPECT_THROW ( utils::Json_element c = utils::Json_element ( ptr ), std::runtime_error );
    EXPECT_THROW ( utils::Json_element e = utils::Json_element ( "This is not a json string" ), std::runtime_error );
}
