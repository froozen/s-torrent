#ifndef STRETCH_GUARD
#define STRETCH_GUARD

#include "layout.h"
#include "window.h"
#include "element.h"
#include "orientation.h"

#include <memory>
#include <vector>

namespace ncurses
{
    struct Resize_data
    {
        Resize_data (
                std::vector < std::shared_ptr < Element > >* elements,
                std::shared_ptr < Window > window,
                std::shared_ptr < Orientation > orientation
                );

        std::shared_ptr < Window > window;
        std::vector < std::shared_ptr < Element > >* elements;
        int prefered_length_sum;
        int total_length_sum;
        int no_preference_element_count;
    };

    class Stretch_layout : public Layout
    {
        public:
            Stretch_layout () = default;

            void update_elements (
                    std::vector < std::shared_ptr < Element > > elements,
                    char key,
                    std::shared_ptr < Window > window
                    );

            void set_orientation ( std::shared_ptr < Orientation > orientation );

            virtual ~Stretch_layout () = default;

        private:
            bool has_input_changed (
                    std::vector < std::shared_ptr < Element > > elements,
                    std::shared_ptr < Window > window
                    );
            void resize (
                    std::vector < std::shared_ptr < Element > > elements,
                    std::shared_ptr < Window > window
                    );

            // resize sub-methods
            std::vector < std::shared_ptr < Window_dummy > > generate_window_dummies ( Resize_data& resize_data );
            int generate_no_preference_length ( Resize_data& resize_data );
            std::vector < std::shared_ptr < Window_dummy > > generate_basic_window_dummies ( Resize_data& resize_data );
            void compress_window_dummies (
                    Resize_data& resize_data,
                    std::vector < std::shared_ptr < Window_dummy > >& window_dummies
                    );

            void distribute_remaining_length (
                    Resize_data& resize_data,
                    std::vector < std::shared_ptr < Window_dummy > >& window_dummies
                    );

            Window_dummy last_window;
            std::vector < std::shared_ptr < Element > > last_elements;
            std::vector < std::shared_ptr < Window > > windows;
            std::shared_ptr < Orientation > orientation;
    };
}

#endif //STRETCH_GUARD
