#ifndef ALERT_EVENT_CREATOR_GUARD
#define ALERT_EVENT_CREATOR_GUARD

#include <thread>

namespace torrent
{
    class Alert_event_creator
    {
        public:
            Alert_event_creator () = default;

            void start ();

            virtual ~Alert_event_creator () = default;

        private:
            void do_event_creation ();
            std::thread event_creator_thread;
    };
}

#endif //ALERT_EVENT_CREATOR_GUARD
