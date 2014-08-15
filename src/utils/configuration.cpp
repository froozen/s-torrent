#include "configuration.h"
#include <fstream>
#include <exception>

namespace utils
{
    std::shared_ptr < Configuration > Configuration::configuration_instance;

    Configuration::Configuration () :
        root ( std::make_shared < Json::Value > () )
    {
        std::ifstream config_file ( "config.json" );
        if ( config_file.is_open () )
        {
            // Read the whole file at once
            std::string content ( ( std::istreambuf_iterator < char > ( config_file ) ), std::istreambuf_iterator < char > () );

            Json::Reader reader;
            bool success = reader.parse ( content, *root );
            if ( !success )
            {
                throw std::runtime_error ( "Error: Failed to parse config file" );
            }
        }
        else
            throw std::runtime_error ( "Error: Couldn't open config file" );
    }

    std::shared_ptr < Configuration > Configuration::get_configuration ()
    {
        if ( configuration_instance.get () == nullptr )
        {
            configuration_instance = std::shared_ptr < Configuration > ( new Configuration () );
        }

        return configuration_instance;
    }

    void Configuration::save ()
    {
        std::ofstream save_file ( "config.json", std::ios::trunc );
        Json::StyledWriter writer;
        save_file << writer.write ( *root ) << std::endl;
    }

    // Getters
    bool Configuration::get_bool ( std::string identifier )
    {
        if ( ( *root ) [ identifier ].isBool () )
            return ( *root ) [ identifier ].asBool ();
        else
            return DEFAULT_BOOL;
    }

    int Configuration::get_int ( std::string identifier )
    {
        if ( ( *root ) [ identifier ].isInt () )
            return ( *root ) [identifier].asInt ();
        else
            return DEFAULT_INT;
    }

    std::string Configuration::get_string ( std::string identifier )
    {
        if ( ( *root ) [ identifier ].isString () )
            return ( *root ) [ identifier ].asString ();
        else
            return DEFAULT_STRING;
    }

    double Configuration::get_double ( std::string identifier )
    {
        if ( ( *root ) [ identifier ].isDouble () )
            return ( *root ) [ identifier ].asDouble ();
        else
            return DEFAULT_DOUBLE;
    }

    // Setters
    void Configuration::set_bool ( std::string identifier, bool value )
    {
        ( *root ) [ identifier ] = value;
    }

    void Configuration::set_int ( std::string identifier, int value )
    {
        ( *root ) [ identifier ] = value;
    }

    void Configuration::set_string ( std::string identifier, std::string value )
    {
        ( *root ) [ identifier ] = value;
    }

    void Configuration::set_double ( std::string identifier, double value )
    {
        ( *root ) [ identifier ] = value;
    }
}
