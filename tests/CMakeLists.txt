find_package ( GTest REQUIRED )
include_directories ( ${GTEST_INCLUDE_DIRS} )
find_package ( Threads REQUIRED )
include_directories ( ${JsonCpp_INCLUDE_DIRS} )
find_package ( JsonCpp REQUIRED )

file ( GLOB_RECURSE TEST_SRCS ${CMAKE_CURRENT_LIST_DIR} *.cpp )
include_directories ( ${CMAKE_CURRENT_LIST_DIR} )

add_executable ( test_executable ${TEST_SRCS} )
target_link_libraries ( test_executable ${GTEST_BOTH_LIBRARIES} core events )
