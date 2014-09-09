#ifndef TORRENT_STATE_GUARD
#define TORRENT_STATE_GUARD

#include "utils/json.h"

namespace torrent
{
    class State
    {
        public:
            static void load ();
            static void save ();

        private:
            static utils::Json_element state;
    };
}

#endif //TORRENT_STATE_GUARD
