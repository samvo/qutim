FIND_PATH(WINTHINGS_INCLUDE_DIR "WinThings/" PATH_SUFFIXES include)
FIND_LIBRARY(WINTHINGS_LIBRARIES wapicwrapper PATH_SUFFIXES lib)

if(WINTHINGS_LIBRARIES AND WINTHINGS_INCLUDE_DIR)
	message( STATUS "Found WinThings: ${WINTHINGS_LIBRARIES}")
	set( WINTHINGS_FOUND 1)
else(WINTHINGS_LIBRARIES AND WINTHINGS_INCLUDE_DIR)
	message( STATUS "Could NOT find WinThings")
	set( WINTHINGS_FOUND 0)
endif(WINTHINGS_LIBRARIES AND WINTHINGS_INCLUDE_DIR)
