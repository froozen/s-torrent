#ifndef EVENT_GUARD
#define EVENT_GUARD

#include <string>

namespace events
{
    class Event
    {
        public:
            Event () = default;

            virtual std::string get_type () = 0;

            virtual ~Event () = default;
    };
}

#endif //EVENT_GUARD
