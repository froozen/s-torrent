#include <gtest/gtest.h>
#include "client/data_formatting.h"

class DataFormattingTest : public testing::Test
{
    public:
        DataFormattingTest () = default;

        virtual void SetUp ()
        {
            normal = 36;
            kilo = 8400;
            mega = 12300000;
            giga = 4700000000;
            zero = 0;
        }

        virtual ~DataFormattingTest () = default;

        double normal, kilo, mega, giga, zero;
};

TEST_F ( DataFormattingTest, SizeTest )
{
    EXPECT_EQ ( "36.0  B", client::to_file_size ( normal ) );
    EXPECT_EQ ( "8.4 KB", client::to_file_size ( kilo ) );
    EXPECT_EQ ( "12.3 MB", client::to_file_size ( mega ) );
    EXPECT_EQ ( "4.7 GB", client::to_file_size ( giga ) );
    EXPECT_EQ ( "0.0  B", client::to_file_size ( zero ) );
}

TEST_F ( DataFormattingTest, SpeedTest )
{
    EXPECT_EQ ( "36.0   B/s", client::to_transfer_speed ( normal ) );
    EXPECT_EQ ( "8.4 KiB/s", client::to_transfer_speed ( kilo ) );
    EXPECT_EQ ( "12.3 MiB/s", client::to_transfer_speed ( mega ) );
    EXPECT_EQ ( "4.7 GiB/s", client::to_transfer_speed ( giga ) );
    EXPECT_EQ ( "0.0   B/s", client::to_transfer_speed ( zero ) );
}

TEST_F ( DataFormattingTest, PercentageTest )
{
    EXPECT_EQ ( "42.85%", client::to_percentage ( 0.42846 ) );
    EXPECT_EQ ( "4.56%", client::to_percentage ( 0.04556 ) );
}

TEST_F ( DataFormattingTest, TruncateDoubleTest )
{
    EXPECT_EQ ( "483.995", client::truncate_double ( 483.9946, 3 ) );
    EXPECT_EQ ( "0.00", client::truncate_double ( 0.001, 2 ) );
}

TEST_F ( DataFormattingTest, DurationTest )
{
    EXPECT_EQ ( "0s", client::to_duration ( 0 ) );
    EXPECT_EQ ( "1s", client::to_duration ( 1 ) );
    EXPECT_EQ ( "1h 33m", client::to_duration ( 60 * 60 + 33 * 60 ) );
    EXPECT_EQ ( "1h 33m", client::to_duration ( 60 * 60 + 33 * 60 + 12 ) );
    EXPECT_EQ ( "1y 1w 1d 1h 1m 1s", client::to_duration (
                52 * 7 * 24 * 60 * 60 +
                7 * 24 * 60 * 60 +
                24 * 60 * 60 +
                60 * 60 +
                60 +
                1,
                6 ) );
}
