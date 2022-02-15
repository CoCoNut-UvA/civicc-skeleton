file(GLOB _ARGP_OSX_ROOT_HINT "/opt/homebrew/Cellar/argp-standalone/*")

set(_ARGP_ROOT_HINTS
    "${_ARGP_OSX_ROOT_HINT}"
)

set(_ARGP_ROOT_PATHS
    "$ENV{PROGRAMFILES}/argp"
)

find_path(ARGP_ROOT_DIR
    NAMES
        include/argp.h
    HINTS
        ${_ARGP_ROOT_HINTS}
    PATHS
        ${_ARGP_ROOT_PATHS}
)
mark_as_advanced(ARGP_ROOT_DIR)

find_path(ARGP_INCLUDE_DIR
    NAMES
        argp.h
    PATHS
        ${ARGP_ROOT_DIR}/include
)

find_library(ARGP_LIBRARY
    NAMES
        argp
    PATHS
        ${ARGP_ROOT_DIR}/lib
)

if (ARGP_LIBRARY)
  set(ARGP_LIBRARIES
      ${ARGP_LIBRARIES}
      ${ARGP_LIBRARY}
  )
endif (ARGP_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ARGP DEFAULT_MSG ARGP_LIBRARIES ARGP_INCLUDE_DIR)

# show the ARGP_INCLUDE_DIR and ARGP_LIBRARIES variables only in the advanced view
mark_as_advanced(ARGP_INCLUDE_DIR ARGP_LIBRARIES)