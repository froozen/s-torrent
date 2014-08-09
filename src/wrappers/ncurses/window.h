#ifndef NCURSES_WINDOW_GUARD
#define NCURSES_WINDOW_GUARD

#include <ncurses.h>
#include <memory>
#include <string>

namespace ncurses
{
    class Window
    {
        public:
            Window ( WINDOW* );
            Window ( int x, int y, int width, int height );

            static const int DEFAULT    = -1;
            static const int BLACK      =  0;
            static const int RED        =  1;
            static const int GREEN      =  2;
            static const int YELLOW     =  3;
            static const int BLUE       =  4;
            static const int MAGENTA    =  5;
            static const int CYAN       =  6;
            static const int WHITE      =  7;

            void move ( int x, int y );
            void print_string ( std::string s );
            void add_character ( char c );
            void set_color ( int fg, int bg );
            void draw_border ();
            void refresh ();

            int get_x () const { return this->x; }
            int get_y () const { return this->y; }
            int get_width () const { return this->width; }
            int get_height () const { return this->height; }

            virtual ~Window ();

        private:
            WINDOW* window;
            int height, width, x, y;
    };
}

#endif //NCURSES_WINDOW_GUARD
