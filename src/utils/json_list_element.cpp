#include "json_list_element.h"
#include "json_element.h"
#include <exception>

#include "json_access.hpp"

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

    int Json_list_element::size ()
    {
        return value->size ();
    }
    // Getters
    bool Json_list_element::get_bool ( int identifier ) const
    {
        return json_access::get_bool ( value, identifier );
    }

    int Json_list_element::get_int ( int identifier ) const
    {
        return json_access::get_int ( value, identifier );
    }

    std::string Json_list_element::get_string ( int identifier ) const
    {
        return json_access::get_string ( value, identifier );
    }

    double Json_list_element::get_double ( int identifier ) const
    {
        return json_access::get_double ( value, identifier );
    }

    size_t Json_list_element::get_size_t ( int identifier ) const
    {
        return json_access::get_size_t ( value, identifier );
    }

    Json::Value* Json_list_element::get_value () const
    {
        return value;
    }

    std::shared_ptr < Json_element > Json_list_element::get_element ( int identifier ) const
    {
        return json_access::get_element ( value, identifier, std::to_string ( identifier ) );
    }

    std::shared_ptr < Json_list_element > Json_list_element::get_list_element ( int identifier ) const
    {
        return json_access::get_list_element ( value, identifier, std::to_string ( identifier ) );
    }

    // Setters
    void Json_list_element::set_bool ( int identifier, bool new_value )
    {
        json_access::set_bool ( value, identifier, new_value );
    }

    void Json_list_element::set_int ( int identifier, int new_value )
    {
        json_access::set_int ( value, identifier, new_value );
    }

    void Json_list_element::set_string ( int identifier, std::string new_value )
    {
        json_access::set_string ( value, identifier, new_value );
    }

    void Json_list_element::set_double ( int identifier, double new_value )
    {
        json_access::set_double ( value, identifier, new_value );
    }

    void Json_list_element::set_size_t ( int identifier, size_t new_value )
    {
        json_access::set_size_t ( value, identifier, new_value );
    }

    void Json_list_element::set_element ( int identifier, const Json_element& new_value )
    {
        json_access::set_element ( value, identifier, new_value );
    }

    void Json_list_element::set_list_element ( int identifier, const Json_list_element& new_value )
    {
        json_access::set_list_element ( value, identifier, new_value );
    }

    // Appending
    void Json_list_element::append_bool ( bool new_value )
    {
        value->append ( new_value );
    }

    void Json_list_element::append_int ( int new_value )
    {
        value->append ( new_value );
    }

    void Json_list_element::append_string ( std::string new_value )
    {
        value->append ( new_value );
    }

    void Json_list_element::append_double ( double new_value )
    {
        value->append ( new_value );
    }

    void Json_list_element::append_size_t ( size_t new_value )
    {
        value->append ( ( unsigned int ) new_value );
    }

    void Json_list_element::append_element ( const Json_element& new_value )
    {
        value->append ( * ( new_value.value ) );
    }

    void Json_list_element::append_list_element ( const Json_list_element& new_value )
    {
        value->append ( * ( new_value.value ) );
    }

}
