# Locate TinyXML2 library
# This module defines
# TINYXML2_LIBRARY, the name of the library to link against
# TINYXML2_FOUND, if false, do not try to link to TINYXML2
# TINYXML2_INCLUDE_DIR, where to find tinyxml2.h

find_path(TINYXML2_INCLUDE_DIR tinyxml2.h
	HINTS
	${TINYXML2}
	$ENV{TINYXML2}
	PATH_SUFFIXES include
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
)

# Lookup the libs
find_library(TINYXML2_LIBRARY_TEMP tinyxml2
	HINTS
	${TINYXML2}
	$ENV{TINYXML2}
	PATH_SUFFIXES lib64 lib
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
)

set(TINYXML2_FOUND "NO")

if(TINYXML2_LIBRARY_TEMP)
		# Set the final string here so the GUI reflects the final state.
		set(TINYXML2_LIBRARY ${TINYXML2_LIBRARY_TEMP} CACHE STRING "Where the TINYXML2 Library can be found")
		# Set the temp variable to INTERNAL so it is not seen in the CMake GUI
		set(TINYXML2_LIBRARY_TEMP "${TINYXML2_LIBRARY_TEMP}" CACHE INTERNAL "")

		set(TINYXML2_FOUND "YES")
endif()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(TINYXML2 REQUIRED_VARS TINYXML2_LIBRARY TINYXML2_INCLUDE_DIR)

