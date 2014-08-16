project ( S-TORRENT )
cmake_minimum_required ( VERSION 3.0 )

set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.. )

if ( CMAKE_CXX_COMPILER MATCHES ".*clang" )
    set ( CMAKE_COMPILER_IS_CLANG )
endif ( CMAKE_CXX_COMPILER MATCHES ".*clang" )

if ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )
    list ( APPEND CMAKE_CXX_FLAGS "-std=c++11" )
endif ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )

include_directories ( ${CMAKE_SOURCE_DIR}/src )

add_subdirectory ( ${CMAKE_SOURCE_DIR}/src )
add_subdirectory ( ${CMAKE_SOURCE_DIR}/tests )

add_library ( core )
target_link_libraries ( core asio_wrapper utils )

set ( S-TORRENT_EXECUTABLE_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp )
add_executable ( s-torrent ${S-TORRENT_EXECUTABLE_SRC} )
target_link_libraries ( s-torrent ncurses_wrapper core )
