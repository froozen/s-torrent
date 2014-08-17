file ( GLOB_RECURSE ASIO_WRAPPER_FILES ${CMAKE_CURRENT_LIST_DIR} *.cpp )
add_library ( asio_wrapper ${ASIO_WRAPPER_FILES} )

find_package ( Boost COMPONENTS thread system REQUIRED )
include_directories ( ${Boost_INCLUDE_DIRS} )

find_package ( Threads REQUIRED )

target_link_libraries ( asio_wrapper ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
