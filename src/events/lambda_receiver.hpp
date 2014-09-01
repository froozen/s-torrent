/* 2D-engine, A C++ library wrapping sfml, to be used for 2D games
   Copyright (C) 2014 firecoders

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
   OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef ENGINE_EVENTS_LAMBDA_RECEIVER_GUARD
#define ENGINE_EVENTS_LAMBDA_RECEIVER_GUARD

#include <functional>

#include "receiver.h"

namespace events
{
    template < typename Event_type >
        class Lambda_receiver : public Receiver < Event_type >
        {
            public:
                Lambda_receiver ( std::function < void ( Event_type ) > on_receive );

                virtual void receive ( Event_type event );

                virtual ~Lambda_receiver () noexcept {};
            private:
                std::function < void ( Event_type ) > on_receive;
        };

    template < typename Event_type >
        Lambda_receiver < Event_type >::Lambda_receiver ( std::function < void ( Event_type ) > on_receive ) :
            on_receive ( on_receive )
        {}

    template < typename Event_type >
        void Lambda_receiver < Event_type >::receive ( Event_type event )
        {
            on_receive ( event );
        }
}

#endif // ENGINE_EVENTS_LAMBDA_RECEIVER_GUARD
