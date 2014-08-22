#ifndef READ_LINE_EVENT_GUARD
#define READ_LINE_EVENT_GUARD

#include "events/connection_receiver.h"
#include "event.h"
#include <string>

namespace events
{
    class Read_line_event : public Event
    {
        public:
            Read_line_event ( std::string line, events::Connection_receiver* origin ) :
                line ( line ),
                origin ( origin )
            {}

            std::string get_type () { return "Read_line_event"; }
            std::string get_line () const { return this->line; }
            events::Connection_receiver* get_origin () const { return this->origin; }

            virtual ~Read_line_event () = default;

        private:
            std::string line;
            events::Connection_receiver* origin;
    };
}
#endif //READ_LINE_EVENT_GUARD
