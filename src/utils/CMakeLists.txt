file ( GLOB_RECURSE UTILS_FILES ${CMAKE_CURRENT_LIST_DIR} *.cpp )
add_library ( utils ${UTILS_FILES} )
target_link_libraries ( utils jsoncpp )
