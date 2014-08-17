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

#include "Test_receiver.hpp"
#include "events/Broadcaster.hpp"
#include "events/Receiver_forwarder.hpp"
#include <memory>

using namespace events;

TEST ( engineEventsReceiverForwarder, generalTest )
{
    Broadcaster < int > test_broadcaster;
    std::shared_ptr < Test_receiver < int > > test_receiver = std::make_shared < Test_receiver < int > > ();
    std::shared_ptr < Test_receiver < int > > test_receiver2 = std::make_shared < Test_receiver < int > > ();
    std::shared_ptr < Receiver_forwarder < int > > test_receiver_forwarder = std::make_shared < Receiver_forwarder < int > > ( test_receiver );

    test_broadcaster.subscribe ( test_receiver_forwarder );
    test_broadcaster.receive ( 5 );
    EXPECT_EQ ( 5, test_receiver->result );

    test_receiver_forwarder->redirect ( test_receiver2 );
    test_broadcaster.receive ( 6 );
    EXPECT_EQ ( 5, test_receiver->result );
    EXPECT_EQ ( 6, test_receiver2->result );
}

TEST ( engineEventsReceiverForwarder, nullptrTest )
{
    Broadcaster < int > test_broadcaster;
    std::shared_ptr < Receiver_forwarder < int > > test_receiver_forwarder = std::make_shared < Receiver_forwarder < int > > ( nullptr );

    test_broadcaster.subscribe ( test_receiver_forwarder );
    test_broadcaster.receive ( 5 );
}
