file ( GLOB_RECURSE CLIENT_FILES ${CMAKE_CURRENT_LIST_DIR} *.cpp )

add_library ( client ${CLIENT_FILES} )
