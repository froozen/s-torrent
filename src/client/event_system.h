#ifndef CLIENT_EVENT_SYSTEM_GUARD
#define CLIENT_EVENT_SYSTEM_GUARD

namespace client
{
    class Event_system
    {
        public:
            static void initialize ();

        private:
            Event_system () = default;
    };
}

#endif //CLIENT_EVENT_SYSTEM_GUARD
