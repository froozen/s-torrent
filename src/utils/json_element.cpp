#include "json_element.h"
#include "json_list_element.h"
#include <exception>

#include <iostream>
namespace utils
{
    Json_element::Json_element ( Json::Value* value ) :
        value ( value ),
        own ( false )
    {
        if ( !value->isObject () )
            throw std::runtime_error ( "Error in utils::Json_element::Confiuguartion_element : value is not an object" );
    }

    Json_element::Json_element () :
        value ( new Json::Value () ),
        own ( true )
    {}

    Json_element::Json_element ( std::string json_string ) :
        Json_element ()
    {
        Json::Reader reader;
        if ( reader.parse ( json_string, *value ) )
        {
            if ( !value->isObject () )
                throw std::runtime_error ( "Error in utils::Json_element::Confiuguartion_element : value is not an object" );
        }
        else
            throw std::runtime_error ( "Error in utils::Json_element::Confiuguartion_element : Failed to parse json_string" );
    }

    Json_element::~Json_element ()
    {
        if ( own )
            delete value;
    }

    Json_element& Json_element::operator= ( const Json_element& rhs )
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

    std::string Json_element::to_string ()
    {
        Json::StyledWriter writer;
        return writer.write ( *value );
    }

    // Getters
    bool Json_element::get_bool ( std::string identifier ) const
    {
        if ( ( *value ) [ identifier ].isBool () )
            return ( *value ) [ identifier ].asBool ();
        else
            return DEFAULT_BOOL;
    }

    int Json_element::get_int ( std::string identifier ) const
    {
        if ( ( *value ) [ identifier ].isInt () )
            return ( *value ) [ identifier ].asInt ();
        else
            return DEFAULT_INT;
    }

    std::string Json_element::get_string ( std::string identifier ) const
    {
        if ( ( *value ) [ identifier ].isString () )
            return ( *value ) [ identifier ].asString ();
        else
            return DEFAULT_STRING;
    }

    double Json_element::get_double ( std::string identifier ) const
    {
        if ( ( *value ) [ identifier ].isDouble () )
            return ( *value ) [ identifier ].asDouble ();
        else
            return DEFAULT_DOUBLE;
    }

    std::shared_ptr < Json_element > Json_element::get_element ( std::string identifier ) const
    {
        if ( ( *value ) [ identifier ].isObject () )
        {
            return std::make_shared < Json_element > ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error in utils::Confiugarion_element::get_element : Requested element \"" + identifier + "\" is not an object" );
    }

    std::shared_ptr < Json_list_element > Json_element::get_list_element ( std::string identifier ) const
    {
        if ( ( *value ) [ identifier ].isArray () )
        {
            return std::make_shared < Json_list_element > ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error in utils::Json_element::get_list_element : Requested element \"" + identifier + "\" is not an object" );
    }

    // Setters
    void Json_element::set_bool ( std::string identifier, bool new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Json_element::set_int ( std::string identifier, int new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Json_element::set_string ( std::string identifier, std::string new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Json_element::set_double ( std::string identifier, double new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Json_element::set_element ( std::string identifier, const Json_element& new_value )
    {
        ( *value ) [ identifier ] = *new_value.value;
    }

    void Json_element::set_list_element ( std::string identifier, const Json_list_element& new_value )
    {
        ( *value ) [ identifier ] = *new_value.value;
    }
}
