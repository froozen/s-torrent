#ifndef SEND_MESSAGE_EVENT_GUARD
#define SEND_MESSAGE_EVENT_GUARD

#include "event.h"
#include <string>

namespace events
{
    class Send_message_event : public Event
    {
        public:
            Send_message_event ( std::string message ):
                message ( message )
            {}

            std::string get_type () { return "Send_message_event"; };
            std::string get_message () const { return this->message; }

            virtual ~Send_message_event () = default;

        private:
            std::string message;
    };
}

#endif //SEND_MESSAGE_EVENT_GUARD
