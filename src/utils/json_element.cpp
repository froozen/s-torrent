#include "json_element.h"
#include "json_list_element.h"
#include <stdexcept>
#include "json_access.hpp"

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
            throw std::runtime_error ( "Error in utils::Json_element::Confiuguartion_element : Failed to parse json_string:\n" + json_string );
    }

    Json_element::~Json_element ()
    {
        if ( own )
            delete value;
    }

    Json_element::Json_element ( const Json_element& rhs )
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

    std::string Json_element::to_formatted_string ()
    {
        Json::StyledWriter writer;
        return writer.write ( *value );
    }

    std::string Json_element::to_small_string ()
    {
        Json::FastWriter writer;
        return writer.write ( *value );
    }

    // Getters
    bool Json_element::get_bool ( std::string identifier ) const
    {
        return json_access::get_bool ( value, identifier );
    }

    int Json_element::get_int ( std::string identifier ) const
    {
        return json_access::get_int ( value, identifier );
    }

    std::string Json_element::get_string ( std::string identifier ) const
    {
        return json_access::get_string ( value, identifier );
    }

    double Json_element::get_double ( std::string identifier ) const
    {
        return json_access::get_double ( value, identifier );
    }

    size_t Json_element::get_size_t ( std::string identifier ) const
    {
        return json_access::get_size_t ( value, identifier );
    }

    Json::Value* Json_element::get_value () const
    {
        return value;
    }

    std::shared_ptr < Json_element > Json_element::get_element ( std::string identifier ) const
    {
        return json_access::get_element ( value, identifier, identifier );
    }

    std::shared_ptr < Json_list_element > Json_element::get_list_element ( std::string identifier ) const
    {
        return json_access::get_list_element ( value, identifier, identifier );
    }

    // Setters
    void Json_element::set_bool ( std::string identifier, bool new_value )
    {
        json_access::set_bool ( value, identifier, new_value );
    }

    void Json_element::set_int ( std::string identifier, int new_value )
    {
        json_access::set_int ( value, identifier, new_value );
    }

    void Json_element::set_string ( std::string identifier, std::string new_value )
    {
        json_access::set_string ( value, identifier, new_value );
    }

    void Json_element::set_double ( std::string identifier, double new_value )
    {
        json_access::set_double ( value, identifier, new_value );
    }

    void Json_element::set_size_t ( std::string identifier, size_t new_value )
    {
        json_access::set_size_t ( value, identifier, new_value );
    }

    void Json_element::set_element ( std::string identifier, const Json_element& new_value )
    {
        json_access::set_element ( value, identifier, new_value );
    }

    void Json_element::set_list_element ( std::string identifier, const Json_list_element& new_value )
    {
        json_access::set_list_element ( value, identifier, new_value );
    }
}
