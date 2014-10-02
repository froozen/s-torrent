#ifndef CONFIG_GUARD
#define CONFIG_GUARD

#include <memory>
#include <string>
#include "json.h"

namespace utils
{
    class Configuration_element;

    class Configuration
    {
        public:
            // Get root Configuration_element
            static std::shared_ptr < Json_element > get_root ();

            // Save and load from and to file
            static void save ();
            static void load ( std::string path );

            virtual ~Configuration () = default;

        private:
            Configuration ();

            static std::shared_ptr < utils::Json_element > root;
    };

}

#endif //CONFIG_GUARD
