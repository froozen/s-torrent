#ifndef CONFIG_GUARD
#define CONFIG_GUARD

#include <jsoncpp/json/json.h>
#include <memory>
#include "configuration_element.h"

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

}

#endif //CONFIG_GUARD
