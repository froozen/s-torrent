#ifndef CONFIG_GUARD
#define CONFIG_GUARD

#include <jsoncpp/json/json.h>
#include <memory>
#include <string>

namespace utils
{
    class Configuration
    {
        public:
            static std::shared_ptr < Configuration > get_configuration ();
            Json::Value& get_root_value ();

            bool get_bool ( std::string identifier );
            int get_int ( std::string identifier );
            std::string get_string ( std::string identifier );
            double get_double ( std::string identifier );

            void set_bool ( std::string identifier, bool value );
            void set_int  ( std::string identifier, int value );
            void set_string ( std::string identifier, std::string value );
            void set_double ( std::string identifier, double value );

            virtual ~Configuration () = default;

        private:
            Configuration ();

            // Values returned for if something went wrong
            const bool          DEFAULT_BOOL    = false;
            const int           DEFAULT_INT     = -1;
            const std::string   DEFAULT_STRING  = "None";
            const double        DEFAULT_DOUBLE  = -1;

            static std::shared_ptr < Configuration > configuration_instance;
            std::shared_ptr < Json::Value > root;

    };
}

#endif //CONFIG_GUARD
