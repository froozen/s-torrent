file ( GLOB_RECURSE TORRENT_FILES ${CMAKE_CURRENT_LIST_DIR} *.cpp )

find_package ( libtorrent-rasterbar REQUIRED )
include_directories ( libtorrent-raterbar_INCLUDE_DIRS )

find_package ( Boost COMPONENTS system thread REQUIRED )
include_directories ( ${Boost_INCLUDE_DIR} )

add_library ( torrent ${TORRENT_FILES} )
target_link_libraries ( torrent ${libtorrent-rasterbar_LIBRARIES} ${Boost_LIBRARIES} )
