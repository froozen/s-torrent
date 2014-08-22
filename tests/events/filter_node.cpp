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
#include "events/filter_node.hpp"
#include <memory>

using namespace events;

TEST ( engineEventsFilterNode, generalTest )
{
    Filter_node < int > test_filter_node ( [] ( int e ) { return e % 2 == 0; } );
    std::shared_ptr < Test_receiver < int > > test_receiver = std::make_shared < Test_receiver < int > > ();
    test_filter_node.subscribe ( test_receiver );

    test_filter_node.receive ( 2 );
    EXPECT_EQ ( 2, test_receiver->result );

    test_filter_node.receive ( 3 );
    EXPECT_NE ( 3, test_receiver->result );
    EXPECT_EQ ( 2, test_receiver->result );
}
