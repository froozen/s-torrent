#include "json_list_element.h"
#include "json_element.h"
#include <exception>

namespace utils
{
    Json_list_element::Json_list_element ( Json::Value* value ) :
        value ( value ),
        own ( false )
    {
        if ( !value->isArray () )
            throw std::runtime_error ( "Error in utils::Json_list_element::Json_list_element : value is not an array" );
    }

    Json_list_element::Json_list_element () :
        value ( new Json::Value () ),
        own ( true )
    {}

    Json_list_element::Json_list_element ( std::string json_string ) :
        Json_list_element ()
    {
        Json::Reader reader;
        if ( reader.parse ( json_string, *value ) )
        {
            if ( !value->isArray () )
                throw std::runtime_error ( "Error in utils::Json_list_element::Json_list_element : value is not an array" );
        }
        else
            throw std::runtime_error ( "Error in utils::Json_list_element::Json_list_element : Failed to parse json_string" );
    }

    Json_list_element::~Json_list_element ()
    {
        if ( own )
            delete value;
    }

    Json_list_element& Json_list_element::operator= ( const Json_list_element& rhs )
    {
        if ( this != &rhs )
        {
            if ( own )
                delete value;

            own = rhs.own;
            if ( rhs.own )
                value = new Json::Value ( *rhs.value );
            else
                value = rhs.value;
        }
        return *this;
    }

    std::string Json_list_element::to_formatted_string ()
    {
        Json::StyledWriter writer;
        return writer.write ( *value );
    }

    std::string Json_list_element::to_small_string ()
    {
        Json::FastWriter writer;
        return writer.write ( *value );
    }

    // Getters
    bool Json_list_element::get_bool ( int identifier ) const
    {
        if ( ( *value ) [ identifier ].isBool () )
            return ( *value ) [ identifier ].asBool ();
        else
            return DEFAULT_BOOL;
    }

    int Json_list_element::get_int ( int identifier ) const
    {
        if ( ( *value ) [ identifier ].isInt () )
            return ( *value ) [ identifier ].asInt ();
        else
            return DEFAULT_INT;
    }

    std::string Json_list_element::get_string ( int identifier ) const
    {
        if ( ( *value ) [ identifier ].isString () )
            return ( *value ) [ identifier ].asString ();
        else
            return DEFAULT_STRING;
    }

    double Json_list_element::get_double ( int identifier ) const
    {
        if ( ( *value ) [ identifier ].isDouble () )
            return ( *value ) [ identifier ].asDouble ();
        else
            return DEFAULT_DOUBLE;
    }

    std::shared_ptr < Json_element > Json_list_element::get_element ( int identifier ) const
    {
        if ( ( *value ) [ identifier ].isObject () )
        {
            return std::make_shared < Json_element > ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error in utils::Json_list_element::get_element : Requested element \"" + std::to_string ( identifier ) + "\" is not an object" );
    }

    std::shared_ptr < Json_list_element > Json_list_element::get_list_element ( int identifier ) const
    {
        if ( ( *value ) [ identifier ].isArray () )
        {
            return std::make_shared < Json_list_element > ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error in utils::Json_list_element::get_list_element : Requested element \"" + std::to_string ( identifier ) + "\" is not an array" );
    }

    // Setters
    void Json_list_element::set_bool ( int identifier, bool new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Json_list_element::set_int ( int identifier, int new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Json_list_element::set_string ( int identifier, std::string new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Json_list_element::set_double ( int identifier, double new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Json_list_element::set_element ( int identifier, const Json_element& new_value )
    {
        ( *value ) [ identifier ] = *new_value.value;
    }

    void Json_list_element::set_list_element ( int identifier, const Json_list_element& new_value )
    {
        ( *value ) [ identifier ] = *new_value.value;
    }
}
