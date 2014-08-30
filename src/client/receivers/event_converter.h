#ifndef CLIENT_EVENT_CONVERTER_GUARD
#define CLIENT_EVENT_CONVERTER_GUARD

#include <memory>

#include "events/receiver.h"
#include "events/events.h"

namespace client
{
    class Event_converter : public events::Receiver < std::shared_ptr < events::Event > >
    {
        public:
            Event_converter () = default;

            void receive ( std::shared_ptr < events::Event > event );

            virtual ~Event_converter () = default;
    };
}

#endif //CLIENT_EVENT_CONVERTER_GUARD
