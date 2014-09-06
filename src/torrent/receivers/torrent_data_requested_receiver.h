#ifndef TORRENT_DATA_REQUESTED_RECEIVER_GUARD
#define TORRENT_DATA_REQUESTED_RECEIVER_GUARD

#include "events/receiver.h"
#include "torrent/events/events.h"

#include <memory>

namespace torrent
{
    class Torrent_data_requested_receiver :
        public events::Receiver < std::shared_ptr < events::Event > >
    {
        public:
            Torrent_data_requested_receiver () = default;

            void receive ( std::shared_ptr < events::Event > event );

            virtual ~Torrent_data_requested_receiver () noexcept = default;
    };
}

#endif //TORRENT_DATA_REQUESTED_RECEIVER_GUARD
