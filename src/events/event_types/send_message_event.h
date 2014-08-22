#ifndef SEND_MESSAGE_EVENT_GUARD
#define SEND_MESSAGE_EVENT_GUARD

#include "event.h"
#include "events/connection_receiver.h"
#include <string>

namespace events
{
    class Send_message_event : public Event
    {
        public:
            Send_message_event ( std::string message, Connection_receiver* target ):
                message ( message ),
                target ( target )
            {}

            std::string get_type () { return "Send_message_event"; };
            std::string get_message () const { return this->message; }
            Connection_receiver* get_target () const { return this->target; }

            virtual ~Send_message_event () = default;

        private:
            std::string message;
            Connection_receiver* target;
    };
}

#endif //SEND_MESSAGE_EVENT_GUARD
