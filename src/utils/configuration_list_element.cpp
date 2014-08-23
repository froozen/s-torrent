#include "configuration_list_element.h"
#include "configuration_element.h"
#include <exception>

namespace utils
{
    Configuration_list_element::Configuration_list_element ( Json::Value* value ) :
        value ( value ),
        own ( false )
    {
        if ( !value->isArray () )
            throw std::runtime_error ( "Error in utils::Configuration_list_element::Configuration_list_element : value is not an array" );
    }

    Configuration_list_element::Configuration_list_element () :
        value ( new Json::Value () ),
        own ( true )
    {}

    Configuration_list_element::~Configuration_list_element ()
    {
        if ( own )
            delete value;
    }

    Configuration_list_element& Configuration_list_element::operator= ( const Configuration_list_element& rhs )
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

    std::string Configuration_list_element::to_string ()
    {
        Json::StyledWriter writer;
        return writer.write ( *value );
    }

    // Getters
    bool Configuration_list_element::get_bool ( int identifier )
    {
        if ( ( *value ) [ identifier ].isBool () )
            return ( *value ) [ identifier ].asBool ();
        else
            return DEFAULT_BOOL;
    }

    int Configuration_list_element::get_int ( int identifier )
    {
        if ( ( *value ) [ identifier ].isInt () )
            return ( *value ) [ identifier ].asInt ();
        else
            return DEFAULT_INT;
    }

    std::string Configuration_list_element::get_string ( int identifier )
    {
        if ( ( *value ) [ identifier ].isString () )
            return ( *value ) [ identifier ].asString ();
        else
            return DEFAULT_STRING;
    }

    double Configuration_list_element::get_double ( int identifier )
    {
        if ( ( *value ) [ identifier ].isDouble () )
            return ( *value ) [ identifier ].asDouble ();
        else
            return DEFAULT_DOUBLE;
    }

    std::shared_ptr < Configuration_element > Configuration_list_element::get_element ( int identifier )
    {
        if ( ( *value ) [ identifier ].isObject () )
        {
            return std::make_shared < Configuration_element > ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error in utils::Configuration_list_element::get_element : Requested element \"" + std::to_string ( identifier ) + "\" is not an object" );
    }

    std::shared_ptr < Configuration_list_element > Configuration_list_element::get_list_element ( int identifier )
    {
        if ( ( *value ) [ identifier ].isArray () )
        {
            return std::make_shared < Configuration_list_element > ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error in utils::Configuration_list_element::get_list_element : Requested element \"" + std::to_string ( identifier ) + "\" is not an array" );
    }

    // Setters
    void Configuration_list_element::set_bool ( int identifier, bool new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Configuration_list_element::set_int ( int identifier, int new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Configuration_list_element::set_string ( int identifier, std::string new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Configuration_list_element::set_double ( int identifier, double new_value )
    {
        ( *value ) [ identifier ] = new_value;
    }

    void Configuration_list_element::set_element ( int identifier, const Configuration_element& new_value )
    {
        ( *value ) [ identifier ] = *new_value.value;
    }

    void Configuration_list_element::set_list_element ( int identifier, const Configuration_list_element& new_value )
    {
        ( *value ) [ identifier ] = *new_value.value;
    }
}
