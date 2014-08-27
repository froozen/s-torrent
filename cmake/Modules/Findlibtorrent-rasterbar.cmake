# Search for the libtorrent-rasterbar library
#
# libtorrent-rasterbar_FOUND - jsoncpp is available
# libtorrent-rasterbar_INCLUDE_DIRS - jsoncpp include directories
# libtorrent-rasterbar_LIBRARIES - required libraries
# libtorrent-rasterbar_DEFINITIONS - required compiler switches

find_package ( PkgConfig )
pkg_check_modules ( LIBTORRENT-RASTERBAR QUIET jsoncpp )
set ( libtorrent-rasterbar_DEFINITIONS ${LIBTORRENT-RASTERBAR_CFLAGS_OTHER} )

find_path ( LIBTORRENT-RASTERBAR_INCLUDE_DIR NAME peer.hpp
            HINTS ${LIBTORRENT-RASTERBAR_INCLUDEDIR} ${LIBTORRENT-RASTERBAR_INCLUDE_DIRS}
            PATH_SUFFIXES libtorrent )

find_library ( LIBTORRENT-RASTERBAR_LIBRARY NAMES libtorrent-rasterbar torrent-rasterbar
               HINST ${LIBTORRENT-RASTERBAR_LIBDIR} ${LIBTORRENT-RASTERBAR_LIBRARY_DIRS} )

set ( libtorrent-rasterbar_LIBRARIES ${LIBTORRENT-RASTERBAR_LIBRARY} )
set ( libtorrent-rasterbar_INCLUDE_DIRS ${LIBTORRENT-RASTERBAR_INCLUDE_DIR} )

include ( FindPackageHandleStandardArgs )
find_package_handle_standard_args ( libtorrent-rasterbar DEFAULT_MSG
                                    LIBTORRENT-RASTERBAR_LIBRARY LIBTORRENT-RASTERBAR_INCLUDE_DIR )

mark_as_advanced ( LIBTORRENT-RASTERBAR_LIBRARY LIBTORRENT-RASTERBAR_INCLUDE_DIR )
