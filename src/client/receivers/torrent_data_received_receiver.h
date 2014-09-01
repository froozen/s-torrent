#ifndef TORRENT_DATA_RECEIVED_RECEIVER_GUARD
#define TORRENT_DATA_RECEIVED_RECEIVER_GUARD

#include "events/receiver.h"
#include "events/event_types/event.h"

#include <memory>

namespace client
{
    class Torrent_data_received_receiver : public events::Receiver < std::shared_ptr < events::Event > >
    {
        public:
            Torrent_data_received_receiver () = default;

            void receive ( std::shared_ptr < events::Event > event );

            virtual ~Torrent_data_received_receiver () noexcept = default;
    };
}

#endif //TORRENT_DATA_RECEIVED_RECEIVER_GUARD
