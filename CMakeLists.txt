project ( S-TORRENT )
cmake_minimum_required ( VERSION 2.6 )

set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.. )
set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )

if ( CMAKE_CXX_COMPILER MATCHES ".*clang" )
    set ( CMAKE_COMPILER_IS_CLANG )
endif ( CMAKE_CXX_COMPILER MATCHES ".*clang" )

if ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )
    set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )

set ( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0" )

include_directories ( ${CMAKE_SOURCE_DIR}/src )

add_subdirectory ( ${CMAKE_SOURCE_DIR}/src )
add_subdirectory ( ${CMAKE_SOURCE_DIR}/tests )

add_library ( core )
target_link_libraries ( core sockets utils events )

set ( S-TORRENT_CLIENT_SRC ${CMAKE_SOURCE_DIR}/src/client_main.cpp )
add_executable ( s-torrent ${S-TORRENT_CLIENT_SRC} )
target_link_libraries ( s-torrent client ncurses_wrapper core )

set ( S-TORRENT_SERVER_SRC ${CMAKE_SOURCE_DIR}/src/server_main.cpp )
add_executable ( s-torrent-server ${S-TORRENT_SERVER_SRC} )
target_link_libraries ( s-torrent-server core torrent )
