/* 2D-engine, A C++ library wrapping sfml, to be used for 2D games
   Copyright (c) 2014 firecoders

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE. */

#include <gtest/gtest.h>

#include "test_receiver.hpp"
#include "events/broadcaster.hpp"
#include "events/lambda_receiver.hpp"
#include <memory>

using namespace events;

TEST ( engineEventsBroadcaster, generalTest )
{
    Broadcaster < int > test_broadcaster;
    std::shared_ptr < Test_receiver < int > > test_receiver = std::make_shared < Test_receiver < int > > ();

    test_broadcaster.subscribe ( test_receiver );
    test_broadcaster.receive ( 5 );
    EXPECT_EQ ( test_receiver->result, 5 );

    test_broadcaster.unsubscribe ( test_receiver.get () );
    test_broadcaster.receive ( 6 );
    EXPECT_NE ( test_receiver->result, 6 );
    EXPECT_EQ ( test_receiver->result, 5 );
}

TEST ( engineEventsBroadcaster, unsubscribeOnReceive )
{
    Broadcaster < int > test_broadcaster;

    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    auto unsubscribe_on_receive = [ & ] ( int i ) { test_broadcaster.unsubscribe ( test_lambda_receiver.get () ); };
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( unsubscribe_on_receive );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.receive ( 1 );
}

TEST ( engineEventsBroadcaster, subscribeOnReceive )
{
    Broadcaster < int > test_broadcaster;
    std::shared_ptr < Test_receiver < int > > test_receiver = std::make_shared < Test_receiver < int > > ();

    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    auto subscribe_on_receive = [ & ] ( int i ) { test_broadcaster.subscribe ( test_receiver ); };
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( subscribe_on_receive );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.receive ( 1 );

    test_broadcaster.receive ( 2 );
    EXPECT_EQ ( test_receiver->result, 2 );
}

TEST ( engineEventsBroadcaster, sendOnReceive )
{
    Broadcaster < int > test_broadcaster;

    bool sent = false;
    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    auto send_on_receive = [ & ] ( int i ) {
        if ( ! sent )
        {
            test_broadcaster.receive ( 2 );
            sent = true;
        }
    };
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( send_on_receive );

    int count = 1;
    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver_2;
    auto test_order = [ & ] ( int i ) {
        EXPECT_EQ ( count, i );
        count++;
    };
    test_lambda_receiver_2 = std::make_shared < Lambda_receiver < int > > ( test_order );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.subscribe ( test_lambda_receiver_2 );
    test_broadcaster.receive ( 1 );
}

TEST ( engineEventsBroadcaster, unsubscribeOverReceive )
{
    Broadcaster < int > test_broadcaster;

    int result = 0;
    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    auto send_and_unsubscribe = [ & ] ( int i ) {
        result = i;
        test_broadcaster.receive ( 2 );
        test_broadcaster.unsubscribe ( test_lambda_receiver.get () );
    };
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( send_and_unsubscribe );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.receive ( 1 );
    EXPECT_EQ ( result, 1 );
}

TEST ( engineEventsBroadcaster, subscribeOverReceive )
{
    Broadcaster < int > test_broadcaster;
    std::shared_ptr < Test_receiver < int > > test_receiver = std::make_shared < Test_receiver < int > > ();

    bool sent = false;
    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    auto send_and_subscribe = [ & ] ( int i ) {
        if ( !sent )
        {
            sent = true;
            test_broadcaster.receive ( 2 );
            test_broadcaster.subscribe ( test_receiver );
        }
    };
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( send_and_subscribe );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.receive ( 1 );
    EXPECT_EQ ( test_receiver->result, 2 );
}

TEST ( engineEventsBroadcaster, duplicateSubscription )
{
    Broadcaster < int > test_broadcaster;

    int access_count = 0;
    auto count_accesses = [ & ] ( int i ) {
        access_count ++;
    };
    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( count_accesses );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.receive ( 1 );
    EXPECT_EQ ( access_count, 1 );
}

