#include <gtest/gtest.h>
#include <fstream>
#include "utils/json.h"

class JsonListElementTest : public testing::Test
{
    public:
        JsonListElementTest () = default;

        virtual void SetUp ()
        {
            std::string json_string = "[ 123, 0.85, true, \"test_string\", { \"value\": 1 } ]";
            json_list_element = std::make_shared < utils::Json_list_element > ( json_string );
        }

        virtual ~JsonListElementTest () = default;

        std::string old_json_list_element;
        std::shared_ptr < utils::Json_list_element > json_list_element;
};

TEST_F ( JsonListElementTest, ReadingTest )
{
    EXPECT_EQ ( 123, json_list_element->get_int ( 0 ) );
    EXPECT_EQ ( 0.85, json_list_element->get_double ( 1 ) );
    EXPECT_EQ ( true, json_list_element->get_bool ( 2 ) );
    EXPECT_EQ ( "test_string", json_list_element->get_string ( 3 ) );

    std::shared_ptr < utils::Json_element > sub_element = json_list_element->get_element ( 4 );
    EXPECT_EQ ( 1, sub_element->get_int ( "value" ) );
}

TEST_F ( JsonListElementTest, AppendingTest )
{
    json_list_element->append_int ( 124 );
    json_list_element->append_double ( 3.14 );
    json_list_element->append_bool ( true );
    json_list_element->append_string ( "appended string" );

    utils::Json_element element;
    element.set_string ( "result", "success" );
    json_list_element->append_element ( element );

    EXPECT_EQ ( 124, json_list_element->get_int ( 5 ) );
    EXPECT_EQ ( 3.14, json_list_element->get_double ( 6 ) );
    EXPECT_EQ ( true, json_list_element->get_bool ( 7 ) );
    EXPECT_EQ ( "appended string", json_list_element->get_string ( 8 ) );

    std::shared_ptr < utils::Json_element > sub_element = json_list_element->get_element ( 9 );
    EXPECT_EQ ( "success", sub_element->get_string ( "result" ) );
}

TEST_F ( JsonListElementTest, FailedValuesTest )
{
    EXPECT_EQ ( -1, json_list_element->get_int ( 3 ) );
    EXPECT_EQ ( -1, json_list_element->get_double ( 3 ) );
    EXPECT_EQ ( false, json_list_element->get_bool ( 3 ) );
}

TEST_F ( JsonListElementTest, MissingValuesTest )
{
    EXPECT_EQ ( -1, json_list_element->get_int ( 5 ) );
    EXPECT_EQ ( -1, json_list_element->get_double ( 5 ) );
    EXPECT_EQ ( false, json_list_element->get_bool ( 5 ) );
    EXPECT_EQ ( "None", json_list_element->get_string ( 5 ) );
}

TEST_F ( JsonListElementTest, CreatingNewValuesTest )
{
    json_list_element->set_int ( 5, 13 );
    json_list_element->set_double ( 6, 3.14 );
    json_list_element->set_bool ( 7, true );
    json_list_element->set_string ( 8, "a new string" );

    EXPECT_EQ ( 13, json_list_element->get_int ( 5 ) );
    EXPECT_EQ ( 3.14, json_list_element->get_double ( 6 ) );
    EXPECT_EQ ( true, json_list_element->get_bool ( 7 ) );
    EXPECT_EQ ( "a new string", json_list_element->get_string ( 8 ) );
}

TEST_F ( JsonListElementTest, SettingTest )
{
    json_list_element->set_int ( 0, 321 );
    json_list_element->set_double ( 1, 1.5 );
    json_list_element->set_bool ( 2, false );
    json_list_element->set_string ( 3, "another_string" );

    utils::Json_element element;
    element.set_int ( "value", 2 );
    json_list_element->set_element ( 4, element );

    EXPECT_EQ ( 321, json_list_element->get_int ( 0 ) );
    EXPECT_EQ ( 1.5, json_list_element->get_double ( 1 ) );
    EXPECT_EQ ( false, json_list_element->get_bool ( 2 ) );
    EXPECT_EQ ( "another_string", json_list_element->get_string ( 3 ) );

    std::shared_ptr < utils::Json_element > test_element = json_list_element->get_element ( 4 );
    EXPECT_EQ  ( 2, test_element->get_int ( "value" ) );
}

TEST_F ( JsonListElementTest, DeathTest )
{
    EXPECT_THROW ( json_list_element->get_element ( 0 ), std::runtime_error );
    EXPECT_THROW ( json_list_element->get_list_element ( 0 ), std::runtime_error );

    // Create it from something other than an array
    Json::Value not_an_array;
    not_an_array = 1;
    Json::Value* ptr = &not_an_array;
    EXPECT_THROW ( utils::Json_list_element c = utils::Json_list_element ( ptr ), std::runtime_error );
    EXPECT_THROW ( utils::Json_list_element e = utils::Json_list_element ( "This is not a json string" ), std::runtime_error );
}

TEST_F ( JsonListElementTest, SizeTest )
{
    EXPECT_EQ ( 5, json_list_element->size () );
}
