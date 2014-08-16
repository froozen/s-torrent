file ( GLOB_RECURSE NCURSES_WRAPPER_FILES ${CMAKE_CURRENT_LIST_DIR} *.cpp )
find_package ( Curses REQUIRED )
add_library ( ncurses_wrapper ${NCURSES_WRAPPER_FILES} )
target_link_libraries ( ncurses_wrapper ${CURSES_LIBRARIES} )
