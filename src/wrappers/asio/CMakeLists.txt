file ( GLOB_RECURSE ASIO_WRAPPER_FILES ${CMAKE_CURRENT_LIST_DIR} *.cpp )
add_library ( asio_wrapper ${ASIO_WRAPPER_FILES} )
