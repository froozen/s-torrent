#include "configuration_element.h"
#include "configuration_list_element.h"
#include <exception>

#include <iostream>
namespace utils
{
    Configuration_element::Configuration_element ( Json::Value* value ) :
        value ( value ),
        own ( false )
    {
        if ( !value->isObject () )
            throw std::runtime_error ( "Error in utils::Configuration_element::Confiuguartion_element : value is not an object" );
    }

    Configuration_element::Configuration_element () :
        value ( new Json::Value () ),
        own ( true )
    {}

    Configuration_element::~Configuration_element ()
    {
        if ( own )
            delete value;
    }

    Configuration_element& Configuration_element::operator= ( const Configuration_element& rhs )
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

    std::string Configuration_element::to_string ()
    {
        Json::StyledWriter writer;
        return writer.write ( *value );
    }

    // Getters
    bool Configuration_element::get_bool ( std::string identifier )
    {
        if ( ( *value ) [ identifier ].isBool () )
            return ( *value ) [ identifier ].asBool ();
        else
            return DEFAULT_BOOL;
    }

    int Configuration_element::get_int ( std::string identifier )
    {
        if ( ( *value ) [ identifier ].isInt () )
            return ( *value ) [ identifier ].asInt ();
        else
            return DEFAULT_INT;
    }

    std::string Configuration_element::get_string ( std::string identifier )
    {
        if ( ( *value ) [ identifier ].isString () )
            return ( *value ) [ identifier ].asString ();
        else
            return DEFAULT_STRING;
    }

    double Configuration_element::get_double ( std::string identifier )
    {
        if ( ( *value ) [ identifier ].isDouble () )
            return ( *value ) [ identifier ].asDouble ();
        else
            return DEFAULT_DOUBLE;
    }

    std::shared_ptr < Configuration_element > Configuration_element::get_element ( std::string identifier )
    {
        if ( ( *value ) [ identifier ].isObject () )
        {
            return std::make_shared < Configuration_element > ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error in utils::Confiugarion_element::get_element : Requested element \"" + identifier + "\" is not an object" );
    }

    std::shared_ptr < Configuration_list_element > Configuration_element::get_list_element ( std::string identifier )
    {
        if ( ( *value ) [ identifier ].isArray () )
        {
            return std::make_shared < Configuration_list_element > ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error in utils::Configuration_element::get_list_element : Requested element \"" + identifier + "\" is not an object" );
    }

    // Setters
    void Configuration_element::set_bool ( std::string identifier, bool new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Configuration_element::set_int ( std::string identifier, int new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Configuration_element::set_string ( std::string identifier, std::string new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Configuration_element::set_double ( std::string identifier, double new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Configuration_element::set_element ( std::string identifier, const Configuration_element& new_value )
    {
        ( *value ) [ identifier ] = *new_value.value;
    }

    void Configuration_element::set_list_element ( std::string identifier, const Configuration_list_element& new_value )
    {
        ( *value ) [ identifier ] = *new_value.value;
    }
}
