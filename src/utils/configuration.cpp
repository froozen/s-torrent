#include "configuration.h"
#include <fstream>
#include <stdexcept>

namespace utils
{
    std::shared_ptr < utils::Json_element > Configuration::root;

    std::shared_ptr < Json_element > Configuration::get_root ()
    {
        return root;
    }

    void Configuration::save ()
    {
        if ( root != nullptr )
        {
            // Open the file in overwrite mode
            std::ofstream save_file ( "config.json", std::ios::trunc );
            save_file << root->to_formatted_string () << std::endl;
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

            try
            {
                root = std::make_shared < utils::Json_element > ( content );
            }
            catch ( std::runtime_error& e )
            {
                throw std::runtime_error ( "Error in utils::Configuration::load : Failed to parse config file" );
            }
        }
        else
            throw std::runtime_error ( "Error in utils::Configuration::load : Couldn't open file: " + path );
    }
}
