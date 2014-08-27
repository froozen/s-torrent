#ifndef TORRENT_EVENT_SYSTEM_GUARD
#define TORRENT_EVENT_SYSTEM_GUARD

namespace torrent
{
    class Event_system
    {
        public:
            static void initialize ();

        private:
            Event_system () = default;
    };
}

#endif //TORRENT_EVENT_SYSTEM_GUARD
