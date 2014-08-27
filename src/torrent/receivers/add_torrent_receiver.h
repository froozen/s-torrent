#ifndef ADD_TORRENT_RECEIVER_GUARD
#define ADD_TORRENT_RECEIVER_GUARD

#include "events/receiver.h"
#include "torrent/events/events.h"

#include <memory>

namespace torrent
{
    class Add_torrent_receiver : public events::Receiver < std::shared_ptr < events::Event > >
    {
        public:
            Add_torrent_receiver () = default;

            void receive ( std::shared_ptr < events::Event > event );

            virtual ~Add_torrent_receiver () = default;
    };
}

#endif //ADD_TORRENT_RECEIVER_GUARD
