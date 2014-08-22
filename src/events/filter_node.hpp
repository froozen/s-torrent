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

#ifndef ENGINE_EVENTS_FILTER_NODE_GUARD
#define ENGINE_EVENTS_FILTER_NODE_GUARD

#include <memory>
#include <functional>

#include "receiver.h"
#include "subscribable.h"
#include "broadcaster.hpp"

namespace events
{
    template < typename Event_type >
        class Filter_node : public Subscribable < Event_type >, public Receiver < Event_type >
        {
            public:
                Filter_node ( std::function < bool ( Event_type ) > qualifies );

                virtual void subscribe ( std::shared_ptr < Receiver < Event_type > > subscribe );
                virtual void unsubscribe ( Receiver < Event_type >* unsubscribe );
                virtual void receive ( Event_type event );

                virtual ~Filter_node () = default;

            private:
                std::function < bool ( Event_type ) > qualifies_function;
                Broadcaster < Event_type > broadcaster;
        };

    template < typename Event_type >
        Filter_node < Event_type >::Filter_node ( std::function < bool ( Event_type ) > qualifies ) :
            qualifies_function ( qualifies )
        {}

    template < typename Event_type >
        void Filter_node < Event_type >::subscribe ( std::shared_ptr < Receiver < Event_type > > subscriber )
        {
            broadcaster.subscribe ( subscriber );
        }

    template < typename Event_type >
        void Filter_node < Event_type >::unsubscribe ( Receiver < Event_type >* unsubscriber )
        {
            broadcaster.unsubscribe ( unsubscriber );
        }

    template < typename Event_type >
        void Filter_node < Event_type >::receive ( Event_type e )
        {
            if ( qualifies_function ( e ) )
                broadcaster.receive ( e );
        }
}

#endif // ENGINE_EVENTS_FILTER_NODE_GUARD
