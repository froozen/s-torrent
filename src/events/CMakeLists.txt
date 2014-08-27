file ( GLOB_RECURSE EVENTS_FILES ${CMAKE_CURRENT_LIST_DIR} *.cpp )
add_library ( events ${EVENTS_FILES} )

target_link_libraries ( events sockets )
