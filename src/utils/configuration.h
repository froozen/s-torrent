#ifndef CONFIG_GUARD
#define CONFIG_GUARD

#include <jsoncpp/json/json.h>
#include <memory>
#include <string>

namespace utils
{
    class Configuration_element;

    class Configuration
    {
        public:
            static std::shared_ptr < Configuration_element > get_root ();

            static void save ();

            virtual ~Configuration () = default;

        private:
            Configuration ();

            static std::shared_ptr < Json::Value > json_value;
    };

    class Configuration_element
    {
        public:
            Configuration_element ();
            Configuration_element ( Json::Value* root );

            std::string to_string ();

            bool get_bool ( std::string identifier );
            int get_int ( std::string identifier );
            std::string get_string ( std::string identifier );
            double get_double ( std::string identifier );
            Configuration_element get_element ( std::string identifier );

            void set_bool ( std::string identifier, bool new_value );
            void set_int  ( std::string identifier, int new_value );
            void set_string ( std::string identifier, std::string new_value );
            void set_double ( std::string identifier, double new_value );
            void set_element ( std::string identifier, const Configuration_element& new_value );

            virtual ~Configuration_element ();

        private:
            // Values returned for if something went wrong
            const bool          DEFAULT_BOOL    = false;
            const int           DEFAULT_INT     = -1;
            const std::string   DEFAULT_STRING  = "None";
            const double        DEFAULT_DOUBLE  = -1;

            Json::Value* value;
            bool own;
    };
}

#endif //CONFIG_GUARD
