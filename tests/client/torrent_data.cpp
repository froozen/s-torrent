#include <gtest/gtest.h>
#include "client/torrent_data.h"

class TorrentDataTest : public testing::Test
{
    public:
        TorrentDataTest () = default;

        virtual void SetUp ()
        {
            std::string json = "{\"normal\": 36.0, \"kilo\": 8400.0, \"mega\": 12300000.0, \"giga\": 4700000000.0, \"zero\": 0.0}";
            torrent_data  = client::Torrent_data ( json );
        }

        virtual ~TorrentDataTest () = default;

        client::Torrent_data torrent_data;
};

TEST_F ( TorrentDataTest, SizeTest )
{
    EXPECT_EQ ( "36.0  B", torrent_data.get_file_size ( "normal" ) );
    EXPECT_EQ ( "8.4 KB", torrent_data.get_file_size ( "kilo" ) );
    EXPECT_EQ ( "12.3 MB", torrent_data.get_file_size ( "mega" ) );
    EXPECT_EQ ( "4.7 GB", torrent_data.get_file_size ( "giga" ) );
    EXPECT_EQ ( "0.0  B", torrent_data.get_file_size ( "zero" ) );
}

TEST_F ( TorrentDataTest, SpeedTest )
{
    EXPECT_EQ ( "36.0   B/s", torrent_data.get_transfer_speed ( "normal" ) );
    EXPECT_EQ ( "8.4 KiB/s", torrent_data.get_transfer_speed ( "kilo" ) );
    EXPECT_EQ ( "12.3 MiB/s", torrent_data.get_transfer_speed ( "mega" ) );
    EXPECT_EQ ( "4.7 GiB/s", torrent_data.get_transfer_speed ( "giga" ) );
    EXPECT_EQ ( "0.0   B/s", torrent_data.get_transfer_speed ( "zero" ) );
}
