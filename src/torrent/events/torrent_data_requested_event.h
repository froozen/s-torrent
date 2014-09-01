#ifndef TORRENT_DATA_REQUESTED_EVENT_GUARD
#define TORRENT_DATA_REQUESTED_EVENT_GUARD

#include "events/event_types/event.h"
#include "utils/json.h"
#include "events/connection_receiver.h"

#include <memory>

namespace torrent
{
    class Torrent_data_requested_event : public events::Event
    {
        public:
            Torrent_data_requested_event ( const utils::Json_element& json, events::Connection_receiver* origin ):
                origin ( origin )
            {}

            std::string get_type () { return "Torrent_data_requested_event"; }
            events::Connection_receiver* get_origin () const { return origin; }

            virtual ~Torrent_data_requested_event () noexcept = default;

        private:
            events::Connection_receiver* origin;
    };
}

#endif //TORRENT_DATA_REQUESTED_EVENT_GUARD
