#ifndef TORRENT_STATE_GUARD
#define TORRENT_STATE_GUARD

#include "utils/json.h"

#include <memory>
#include <vector>

namespace torrent
{
    class State
    {
        public:
            static void load ();
            static void save ();
            static std::vector < std::shared_ptr < utils::Json_element > > get_torrent_states ();
            static void add_torrent_state ( const utils::Json_element& torrent_state );

        private:
            static utils::Json_element state;
    };
}

#endif //TORRENT_STATE_GUARD
