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
#include "events/Lambda_receiver.hpp"
#include <memory>

using namespace events;

TEST ( engineEventsLambdaReceiver, generalTest )
{
    Broadcaster < int > test_broadcaster;
    int result = 0;
    auto lambda = [&] ( int i ) { result = i; };
    std::shared_ptr < Lambda_receiver < int > > lambda_receiver = std::make_shared < Lambda_receiver < int > > ( lambda );

    test_broadcaster.subscribe ( lambda_receiver );
    test_broadcaster.receive ( 5 );
    EXPECT_EQ ( 5, result );
}
