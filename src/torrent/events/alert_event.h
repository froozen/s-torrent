#ifndef ALERT_EVENT_GUARD
#define ALERT_EVENT_GUARD
#define BOOST_ASIO_DYN_LINK

#include "events/event_types/event.h"

#include <memory>
#include <string>
#include <libtorrent/alert.hpp>

namespace torrent
{
    class Alert_event : public events::Event
    {
        public:
            Alert_event ( std::shared_ptr < libtorrent::alert > alert ) :
                alert ( alert )
            {}

            std::string get_type () { return "Alert_event"; }
            std::shared_ptr < libtorrent::alert > get_alert () const { return alert; }

            virtual ~Alert_event () = default;

        private:
            std::shared_ptr < libtorrent::alert > alert;
    };
}

#endif //ALERT_EVENT_GUARD
