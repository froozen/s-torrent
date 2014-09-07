#ifndef CONNECTION_STATUS_RECEIVER_GUARD
#define CONNECTION_STATUS_RECEIVER_GUARD

#include "events/receiver.h"
#include "events/event_types/event.h"

#include <memory>

namespace client
{
    class Connection_status_receiver : public events::Receiver < std::shared_ptr < events::Event > >
    {
        public:
            Connection_status_receiver () = default;

            void receive ( std::shared_ptr < events::Event > event );

            virtual ~Connection_status_receiver () noexcept = default;
    };
}

#endif //CONNECTION_STATUS_RECEIVER_GUARD
