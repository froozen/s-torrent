file ( GLOB_RECURSE SOCKETS_FILES ${CMAKE_CURRENT_LIST_DIR} *.cpp )
add_library ( sockets ${SOCKETS_FILES} )

find_package ( Threads REQUIRED )

target_link_libraries ( sockets ${CMAKE_THREAD_LIBS_INIT} )
