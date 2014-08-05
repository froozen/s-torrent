project ( S-TORRENT )
cmake_minimum_required ( VERSION 3.0 )

set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.. )

if ( CMAKE_COMPILER_IS_GNUCXX )
    list ( APPEND CMAKE_CXX_FLAGS "-std=c++11" )
endif ( CMAKE_COMPILER_IS_GNUCXX )


set ( S-TORRENT_EXECUTABLE_SRC main.cpp )
add_executable ( s-torrent ${S-TORRENT_EXECUTABLE_SRC} )
