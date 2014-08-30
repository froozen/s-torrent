#ifndef SHARED_DATA_GUARD
#define SHARED_DATA_GUARD

#include <memory>
#include <vector>
#include <mutex>

#include "torrent_data.h"

namespace client
{
    class Shared_data
    {
        public:
            static void set_torrent_data ( std::shared_ptr < std::vector < std::shared_ptr < Torrent_data > > > new_torrent_data );
            static std::shared_ptr < std::vector < std::shared_ptr < Torrent_data > > > get_torrent_data ();

            virtual ~Shared_data () = default;

        private:
            Shared_data () = default;

            static std::shared_ptr < std::vector < std::shared_ptr < Torrent_data > > > torrent_data;
            static std::mutex torrent_data_mutex;
    };
}

#endif //SHARED_DATA_GUARD
