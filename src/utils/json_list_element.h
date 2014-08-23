#ifndef CONFIGURATION_LIST_ELEMENT_GUARD
#define CONFIGURATION_LIST_ELEMENT_GUARD

#include <jsoncpp/json/json.h>
#include <memory>
#include <string>

namespace utils
{
    class Json_element;

    class Json_list_element
    {
        public:
            Json_list_element ();
            Json_list_element ( Json::Value* root );
            Json_list_element ( std::string json_string );

            Json_list_element& operator= ( const Json_list_element& rhs );

            std::string to_formatted_string ();
            std::string to_small_string ();

            bool get_bool ( int identifier ) const;
            int get_int ( int identifier ) const;
            std::string get_string ( int identifier ) const;
            double get_double ( int identifier ) const;
            std::shared_ptr < Json_element > get_element ( int identifier ) const;
            std::shared_ptr < Json_list_element > get_list_element ( int identifier ) const;

            void set_bool ( int identifier, bool new_value );
            void set_int  ( int identifier, int new_value );
            void set_string ( int identifier, std::string new_value );
            void set_double ( int identifier, double new_value );
            void set_element ( int identifier, const Json_element& new_value );
            void set_list_element ( int identifier, const Json_list_element& new_value );

            virtual ~Json_list_element ();

            friend class Json_element;

        private:
            // Values returned if something went wrong
            const bool          DEFAULT_BOOL    = false;
            const int           DEFAULT_INT     = -1;
            const std::string   DEFAULT_STRING  = "None";
            const double        DEFAULT_DOUBLE  = -1;

            Json::Value* value;
            bool own;
    };
}

#endif //CONFIGURATION_LIST_ELEMENT_GUARD
