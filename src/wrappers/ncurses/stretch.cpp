#include "stretch.h"
#include <algorithm>

namespace ncurses
{
    Resize_data::Resize_data (
            const std::vector < std::shared_ptr < Element > >* elements,
            const std::shared_ptr < Window >& window,
            const std::shared_ptr < Orientation >& orientation
            ):
        window ( window ),
        elements ( elements ),
        total_length_sum ( 0 )
    {
        // prefered_length_sum
        prefered_length_sum = 0;
        std::for_each ( elements->begin (), elements->end (),
                [ & ] ( std::shared_ptr < Element > element )
                    { prefered_length_sum += orientation->get_prefered_length ( element ); } );

        // no_preference_element_count
        no_preference_element_count = std::count_if ( elements->begin (), elements->end (),
                [ & ] ( std::shared_ptr < Element > element )
                    { return orientation->get_prefered_length ( element ) == 0; } );
    }

    void Stretch_layout::update_elements (
            const std::vector < std::shared_ptr < Element > >& elements,
            char key,
            const std::shared_ptr < Window >& window
            )
    {
        if ( orientation.get () != nullptr )
        {
            if ( has_input_changed ( elements, window ) )
                resize ( elements, window );

            if ( windows.size () == elements.size () )
            {
                for ( int i = 0; i < elements.size (); i++ )
                {
                    elements.at ( i )->update ( key, windows.at ( i ) );
                }
            }
        }
        else
        {
            window->print_string ( "Missing Orientation!" );
            window->refresh ();
        }
    }

    void Stretch_layout::set_orientation ( const std::shared_ptr < Orientation >& orientation )
    {
        this->orientation = orientation;
    }

    bool Stretch_layout::has_input_changed (
            const std::vector < std::shared_ptr < Element > >& elements,
            const std::shared_ptr < Window >& window
            )
    {
        return ! (
                elements == last_elements &&
                window->get_x () == last_window.x &&
                window->get_y () == last_window.y &&
                window->get_width () == last_window.width &&
                window->get_height () == last_window.height
                );
    }

    void Stretch_layout::resize (
            const std::vector < std::shared_ptr < Element > >& elements,
            const std::shared_ptr < Window >& window
            )
    {
        windows.clear ();
        Resize_data resize_data ( &elements, window, orientation );

        std::vector < std::shared_ptr < Window_dummy > > window_dummies = generate_window_dummies ( resize_data );
        for ( auto it = window_dummies.begin (); it != window_dummies.end (); it++ )
        {
            std::shared_ptr < Window > element_window = std::make_shared < Window > (
                    ( *it )->x,
                    ( *it )->y,
                    ( *it )->width,
                    ( *it )->height
                    );
            windows.push_back ( element_window );
        }
    }

    std::vector < std::shared_ptr < Window_dummy > > Stretch_layout::generate_window_dummies ( Resize_data& resize_data )
    {
        std::vector < std::shared_ptr < Window_dummy > > window_dummies = generate_basic_window_dummies ( resize_data );
        compress_window_dummies ( resize_data, window_dummies );
        distribute_remaining_length ( resize_data, window_dummies );

        return window_dummies;
    }

    int Stretch_layout::generate_no_preference_length ( Resize_data& resize_data )
    {
        if ( resize_data.prefered_length_sum > orientation->get_primary_length ( resize_data.window ) )
            return resize_data.prefered_length_sum / ( resize_data.elements->size () - resize_data.no_preference_element_count );
        else
            return ( orientation->get_primary_length ( resize_data.window ) - resize_data.prefered_length_sum )
                / resize_data.no_preference_element_count;
    }

    std::vector < std::shared_ptr < Window_dummy > > Stretch_layout::generate_basic_window_dummies ( Resize_data& resize_data )
    {
        std::vector < std::shared_ptr < Window_dummy > > basic_dummies;
        int no_preference_length = generate_no_preference_length ( resize_data );

        for ( int i = 0; i < resize_data.elements->size (); i++ )
        {
            std::shared_ptr < Window_dummy > next_window_dummy = std::make_shared < Window_dummy > ();
            orientation->set_secondary_length ( next_window_dummy, orientation->get_secondary_length ( resize_data.window ) );
            orientation->set_secondary_coordinate ( next_window_dummy, orientation->get_secondary_coordinate ( resize_data.window ) );
            orientation->set_primary_coordinate ( next_window_dummy,
                    orientation->get_primary_coordinate ( resize_data.window ) + resize_data.total_length_sum );

            if ( orientation->get_prefered_length ( resize_data.elements->at ( i ) ) > 0 )
                orientation->set_primary_length ( next_window_dummy, orientation->get_prefered_length ( resize_data.elements->at ( i ) ) );
            else
                orientation->set_primary_length ( next_window_dummy, no_preference_length );

            resize_data.total_length_sum += orientation->get_primary_length ( next_window_dummy );
            basic_dummies.push_back ( next_window_dummy );
        }

        return basic_dummies;
    }

    void Stretch_layout::compress_window_dummies (
            Resize_data& resize_data,
            std::vector < std::shared_ptr < Window_dummy > >& window_dummies
            )
    {
        if ( resize_data.total_length_sum > orientation->get_primary_length ( resize_data.window ) )
        {
            if ( orientation->get_primary_length( resize_data.window ) < resize_data.elements->size () )
                window_dummies.clear ();

            for ( auto it = window_dummies.begin (); it != window_dummies.end (); it++ )
            {
                orientation->set_primary_length ( *it,
                        orientation->get_primary_length ( resize_data.window ) *
                        ( ( float ) orientation->get_primary_length ( *it ) / resize_data.total_length_sum ) );

                resize_data.total_length_sum += orientation->get_primary_length ( *it );
            }

            for ( auto it = window_dummies.begin () + 1; it != window_dummies.end (); it++ )
            {
                orientation->set_primary_coordinate ( *it,
                        orientation->get_primary_coordinate ( *( it - 1 ) ) +
                        orientation->get_primary_length ( *( it - 1 ) )
                        );
            }

            resize_data.total_length_sum =
                orientation->get_primary_length ( window_dummies.back () ) +
                orientation->get_primary_coordinate ( window_dummies.back () ) -
                orientation->get_primary_coordinate ( window_dummies.front () );
        }
    }

    void Stretch_layout::distribute_remaining_length (
            Resize_data& resize_data,
            std::vector < std::shared_ptr < Window_dummy > >& window_dummies
            )
    {
        if ( !window_dummies.empty () )
        {
            int index = 0;
            while ( resize_data.total_length_sum < orientation->get_primary_length ( resize_data.window ) )
            {
                if (
                        orientation->get_prefered_length ( resize_data.elements->at ( index ) ) == 0 ||
                        resize_data.no_preference_element_count == 0 ||
                        orientation->get_primary_length ( window_dummies.at ( index ) ) <
                        orientation->get_prefered_length ( resize_data.elements->at ( index ) )
                   )
                {
                    orientation->set_primary_length ( window_dummies.at ( index ),
                            orientation->get_primary_length ( window_dummies.at ( index ) ) + 1 );

                    resize_data.total_length_sum++;

                    for ( int i = index + 1; i < window_dummies.size (); i++ )
                    {
                        orientation->set_primary_coordinate ( window_dummies.at ( i ),
                            orientation->get_primary_coordinate ( window_dummies.at ( i ) ) + 1 );
                    }
                }

                index++;
                if ( index == window_dummies.size () )
                    index = 0;
            }
        }
    }
}
