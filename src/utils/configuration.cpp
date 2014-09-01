#include "configuration.h"
#include <fstream>
#include <stdexcept>

namespace utils
{
    std::shared_ptr < Json::Value > Configuration::json_value;

    std::shared_ptr < Json_element > Configuration::get_root ()
    {
        if ( json_value == nullptr )
            throw std::runtime_error ( "Error in utils::Confiugration::get_root : Confinguration file isn't loaded" );

        return std::make_shared < Json_element > ( json_value.get () );
    }

    void Configuration::save ()
    {
        if ( json_value != nullptr )
        {
            // Open the file in overwrite mode
            std::ofstream save_file ( "config.json", std::ios::trunc );
            save_file << get_root ()->to_formatted_string () << std::endl;
        }
        else
            throw std::runtime_error ( "Error in utils::Confiugration::save : Confinguration file isn't loaded" );
    }

    void Configuration::load ( std::string path )
    {
        std::ifstream config_file ( path.c_str () );

        if ( config_file.is_open () )
        {
            // Read the whole file at once
            std::string content ( ( std::istreambuf_iterator < char > ( config_file ) ), std::istreambuf_iterator < char > () );

            Json::Reader reader;
            json_value = std::make_shared < Json::Value > ();
            bool success = reader.parse ( content, *json_value );
            if ( !success )
                throw std::runtime_error ( "Error in utils::Configuration::load : Failed to parse config file" );
        }
        else
            throw std::runtime_error ( "Error in utils::Configuration::load : Couldn't open file: " + path );
    }
}
