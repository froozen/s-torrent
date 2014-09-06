#ifndef JSON_ACCESS_GUARD
#define JSON_ACCESS_GUARD

#include <jsoncpp/json/json.h>
#include <memory>
#include <string>
#include <stdexcept>

#include "json.h"

namespace utils
{
    namespace json_access
    {
        const bool          DEFAULT_BOOL    = false;
        const int           DEFAULT_INT     = -1;
        const std::string   DEFAULT_STRING  = "None";
        const double        DEFAULT_DOUBLE  = -1;
        const size_t        DEFAULT_SIZE_T  = 0;

        // Getters
        template < typename Key >
            bool get_bool ( Json::Value* value,  Key identifier )
            {
                if ( ( *value ) [ identifier ].isBool () )
                    return ( *value ) [ identifier ].asBool ();
                else
                    return DEFAULT_BOOL;
            }

        template < typename Key >
            int get_int ( Json::Value* value,  Key identifier )
            {
                if ( ( *value ) [ identifier ].isNumeric () )
                    return ( *value ) [ identifier ].asInt ();
                else
                    return DEFAULT_INT;
            }

        template < typename Key >
            std::string get_string ( Json::Value* value,  Key identifier )
            {
                if ( ( *value ) [ identifier ].isString () )
                    return ( *value ) [ identifier ].asString ();
                else
                    return DEFAULT_STRING;
            }

        template < typename Key >
            double get_double ( Json::Value* value,  Key identifier )
            {
                if ( ( *value ) [ identifier ].isNumeric () )
                    return ( *value ) [ identifier ].asDouble ();
                else
                    return DEFAULT_DOUBLE;
            }

        template < typename Key >
            size_t get_size_t ( Json::Value* value,  Key identifier )
            {
                if ( ( *value ) [ identifier ].isNumeric () )
                    return ( *value ) [ identifier ].asUInt ();
                else
                    return DEFAULT_SIZE_T;
            }

        template < typename Key >
            std::shared_ptr < Json_element > get_element ( Json::Value* value,  Key identifier, std::string identifier_name )
            {
                if ( ( *value ) [ identifier ].isObject () )
                {
                    return std::make_shared < Json_element > ( & ( ( *value ) [ identifier ] ) );
                }
                throw std::runtime_error ( "Error in utils::Confiugarion_element::get_element : Requested element \"" + identifier_name + "\" is not an object" );
            }

        template < typename Key >
            std::shared_ptr < Json_list_element > get_list_element ( Json::Value* value,  Key identifier, std::string identifier_name )
            {
                if ( ( *value ) [ identifier ].isArray () )
                {
                    return std::make_shared < Json_list_element > ( & ( ( *value ) [ identifier ] ) );
                }
                throw std::runtime_error ( "Error in utils::get_list_element : Requested element \"" + identifier_name + "\" is not an object" );
            }

        // Setters
        template < typename Key >
            void set_bool ( Json::Value* value,  Key identifier, bool new_value )
            {
                ( *value ) [ identifier ] = new_value;
            }

        template < typename Key >
            void set_int ( Json::Value* value,  Key identifier, int new_value )
            {
                ( *value ) [ identifier ] = new_value;
            }

        template < typename Key >
            void set_string ( Json::Value* value,  Key identifier, std::string new_value )
            {
                ( *value ) [ identifier ] = new_value;
            }

        template < typename Key >
            void set_double ( Json::Value* value,  Key identifier, double new_value )
            {
                ( *value ) [ identifier ] = new_value;
            }

        template < typename Key >
            void set_size_t ( Json::Value* value,  Key identifier, size_t new_value )
            {
                ( *value ) [ identifier ] = ( unsigned int ) new_value;
            }

        template < typename Key >
            void set_element ( Json::Value* value,  Key identifier, const Json_element& new_value )
            {
                ( *value ) [ identifier ] = *new_value.get_value ();
            }

        template < typename Key >
            void set_list_element ( Json::Value* value,  Key identifier, const Json_list_element& new_value )
            {
                ( *value ) [ identifier ] = *new_value.get_value ();
            }
    }
}

#endif //JSON_ACCESS_GUARD
