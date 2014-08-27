#ifndef CONFIGURATION_ELEMENT_GUARD
#define CONFIGURATION_ELEMENT_GUARD

#include <jsoncpp/json/json.h>
#include <memory>
#include <string>

namespace utils
{
    class Json_list_element;

    class Json_element
    {
        public:
            Json_element ();
            Json_element ( Json::Value* root );
            Json_element ( std::string json_string );

            Json_element& operator= ( const Json_element& rhs );

            std::string to_formatted_string ();
            std::string to_small_string ();

            bool get_bool ( std::string identifier ) const;
            int get_int ( std::string identifier ) const;
            std::string get_string ( std::string identifier ) const;
            double get_double ( std::string identifier ) const;
            size_t get_size_t ( std::string identifier ) const;
            std::shared_ptr < Json_element > get_element ( std::string identifier ) const;
            std::shared_ptr < Json_list_element > get_list_element ( std::string identifier ) const;

            void set_bool ( std::string identifier, bool new_value );
            void set_int  ( std::string identifier, int new_value );
            void set_string ( std::string identifier, std::string new_value );
            void set_double ( std::string identifier, double new_value );
            void set_size_t ( std::string identifier, size_t new_value );
            void set_element ( std::string identifier, const Json_element& new_value );
            void set_list_element ( std::string identifier, const Json_list_element& new_value );

            virtual ~Json_element ();

            friend class Json_list_element;

        private:
            // Values returned if something went wrong
            const bool          DEFAULT_BOOL    = false;
            const int           DEFAULT_INT     = -1;
            const std::string   DEFAULT_STRING  = "None";
            const double        DEFAULT_DOUBLE  = -1;
            const size_t        DEFAULT_SIZE_T  = 0;

            Json::Value* value;
            bool own;
    };
}

#endif //CONFIGURATION_ELEMENT_GUARD
