#ifndef CONFIGURATION_LIST_ELEMENT_GUARD
#define CONFIGURATION_LIST_ELEMENT_GUARD

#include <jsoncpp/json/json.h>
#include <memory>
#include <string>

namespace utils
{
    class Configuration_element;

    class Configuration_list_element
    {
        public:
            Configuration_list_element ();
            Configuration_list_element ( Json::Value* root );

            Configuration_list_element& operator= ( const Configuration_list_element& rhs );

            std::string to_string ();

            bool get_bool ( int identifier );
            int get_int ( int identifier );
            std::string get_string ( int identifier );
            double get_double ( int identifier );
            std::shared_ptr < Configuration_element > get_element ( int identifier );
            std::shared_ptr < Configuration_list_element > get_list_element ( int identifier );

            void set_bool ( int identifier, bool new_value );
            void set_int  ( int identifier, int new_value );
            void set_string ( int identifier, std::string new_value );
            void set_double ( int identifier, double new_value );
            void set_element ( int identifier, const Configuration_element& new_value );
            void set_list_element ( int identifier, const Configuration_list_element& new_value );

            virtual ~Configuration_list_element ();

            friend class Configuration_element;

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
