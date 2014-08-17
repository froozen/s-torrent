# Search for the jsoncpp library
#
# JsonCpp_FOUND - jsoncpp is available
# JsonCpp_INCLUDE_DIRS - jsoncpp include directories
# JsonCpp_LIBRARIES - required libraries
# JsonCpp_DEFINITIONS - required compiler switches

find_package ( PkgConfig )
pkg_check_modules ( JSON_CPP QUIET jsoncpp )
set ( JsonCpp_DEFINITIONS ${JSON_CPP_CFLAGS_OTHER} )

find_path ( JSON_CPP_INCLUDE_DIR NAME json/json.h
            HINTS ${JSON_CPP_INCLUDEDIR} ${JSON_CPP_INCLUDE_DIRS}
            PATH_SUFFIXES jsoncpp )

find_library ( JSON_CPP_LIBRARY NAMES jsoncpp libjsoncpp
               HINST ${JSON_CPP_LIBDIR} ${JSON_CPP_LIBRARY_DIRS} )

set ( JsonCpp_LIBRARIES ${JSON_CPP_LIBRARY} )
set ( JsonCpp_INCLUDE_DIRS ${JSON_CPP_INCLUDE_DIR} )

include ( FindPackageHandleStandardArgs )
find_package_handle_standard_args ( jsoncpp DEFAULT_MSG
                                    JSON_CPP_LIBRARY JSON_CPP_INCLUDE_DIR )

mark_as_advanced ( JSON_CPP_LIBRARY JSON_CPP_INCLUDE_DIR )
