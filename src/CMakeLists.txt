project ( S-TORRENT )
cmake_minimum_required ( VERSION 3.0 )

set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.. )

if ( CMAKE_CXX_COMPILER MATCHES ".*clang" )
    set ( CMAKE_COMPILER_IS_CLANG )
endif ( CMAKE_CXX_COMPILER MATCHES ".*clang" )

if ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )
    list ( APPEND CMAKE_CXX_FLAGS "-std=c++11" )
endif ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )

find_package ( Boost COMPONENTS thread system REQUIRED )
include_directories ( ${Boost_INCLUDE_DIRS} )

find_package ( Threads REQUIRED )
find_package ( Curses )

include_directories ( ${CMAKE_SOURCE_DIR} )

add_subdirectory ( ${CMAKE_SOURCE_DIR}/wrappers/asio )
add_subdirectory ( ${CMAKE_SOURCE_DIR}/wrappers/ncurses )

set ( S-TORRENT_EXECUTABLE_SRC main.cpp )
add_executable ( s-torrent ${S-TORRENT_EXECUTABLE_SRC} )
target_link_libraries ( s-torrent ${Boost_LIBRARIES} ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} asio_wrapper ncurses_wrapper )
