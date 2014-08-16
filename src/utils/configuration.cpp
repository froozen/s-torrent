#include "configuration.h"
#include <fstream>
#include <exception>

namespace utils
{
    std::shared_ptr < Json::Value > Configuration::json_value;

    std::shared_ptr < Configuration_element > Configuration::get_root ()
    {
        if ( json_value.get () == nullptr )
        {
            std::ifstream config_file ( "config.json" );

            if ( config_file.is_open () )
            {
                // Read the whole file at once
                std::string content ( ( std::istreambuf_iterator < char > ( config_file ) ), std::istreambuf_iterator < char > () );

                Json::Reader reader;
                json_value = std::make_shared < Json::Value > ();
                bool success = reader.parse ( content, *json_value );
                if ( !success )
                    throw std::runtime_error ( "Error: Failed to parse config file" );
            }
            else
                throw std::runtime_error ( "Error: Couldn't open config file" );
        }

        return std::make_shared < Configuration_element > ( json_value.get () );
    }

    void Configuration::save ()
    {
        if ( json_value.get () != nullptr )
        {
            std::shared_ptr < Configuration_element > root = std::make_shared < Configuration_element > ( json_value.get () );
            std::ofstream save_file ( "config.json", std::ios::trunc );
            save_file << root->to_string () << std::endl;
        }
    }


    // Configuration_element
    Configuration_element::Configuration_element ( Json::Value* value ) :
        value ( value ),
        own ( false )
    {}

    Configuration_element::Configuration_element () :
        value ( new Json::Value () ),
        own ( true )
    {}

    Configuration_element::~Configuration_element ()
    {
        if ( own )
            delete value;
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
            return ( *value ) [identifier].asInt ();
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

    Configuration_element Configuration_element::get_element ( std::string identifier )
    {
        if ( ( *value ) [ identifier ].isObject () )
        {
            return Configuration_element ( & ( ( *value ) [ identifier ] ) );
        }
        throw std::runtime_error ( "Error: Requested element ( \"" + identifier + "\") is not an object" );
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
}
