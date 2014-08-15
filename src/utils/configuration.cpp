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
        // Read the whole file at once
        std::string content ( ( std::istreambuf_iterator < char > ( config_file ) ), std::istreambuf_iterator < char > () );

        Json::Reader reader;
        bool success = reader.parse ( content, *root );
        if ( !success )
        {
            throw std::runtime_error ( "Error: Failed to parse config file" );
        }
    }

    std::shared_ptr < Configuration > Configuration::get_configuration ()
    {
        if ( configuration_instance.get () == nullptr )
        {
            configuration_instance = std::shared_ptr < Configuration > ( new Configuration () );
        }

        return configuration_instance;
    }

    // Getters
    bool Configuration::get_bool ( std::string identifier )
    {
        try
        {
            return root->get ( identifier, DEFAULT_BOOL ).asBool ();
        }
        catch ( std::runtime_error& e )
        {
            return DEFAULT_BOOL;
        }
    }

    int Configuration::get_int ( std::string identifier )
    {
        try
        {
            return root->get ( identifier, DEFAULT_INT ).asInt ();
        }
        catch ( std::runtime_error& e )
        {
            return DEFAULT_INT;
        }
    }

    std::string Configuration::get_string ( std::string identifier )
    {
        try
        {
            return root->get ( identifier, DEFAULT_STRING ).asString ();
        }
        catch ( std::runtime_error& e )
        {
            return DEFAULT_STRING;
        }
    }

    double Configuration::get_double ( std::string identifier )
    {
        try
        {
            return root->get ( identifier, DEFAULT_DOUBLE ).asDouble ();
        }
        catch ( std::runtime_error& e )
        {
            return DEFAULT_DOUBLE;
        }
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
