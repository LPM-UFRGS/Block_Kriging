# This module will first look into the directories defined by the variables:
# 1) AR2GEMS_SOURCE_PATH and AR2GEMS_BUILD_PATH 
# 2) windows ar2gems location  in registry
# 
# AR2GEMS_LIBRARIES    - ar2gems libraries to link
# AR2GEMS_INCLUDE_DIRS - The AR2GEMS include directories
#
# AR2GEMS_RELEASE_FOUND     - System has AR2GEMS
# AR2GEMS_DEBUG_FOUND       - System has AR2GEMS
# AR2GEMS_FOUND             - at least one (debug or release) libraries set found
# AR2GEMS_RELEASE_LIBRARIES - The release libraries
# AR2GEMS_DEBUG_LIBRARIES   - The debug libraries

# Other standarnd issue macros
include (FindPackageHandleStandardArgs)
include (FindPackageMessage)

set (FINDAR2GEMS_DEBUG FALSE)  # print debug info

set (AR2GEMS_ALL_RELEASE_LIBS_FOUND TRUE) # internal flag to check if all required libs are found, if atleast one missing this flag set to FALSE
set (AR2GEMS_ALL_DEBUG_LIBS_FOUND TRUE) # internal flag to check if all required libs are found, if atleast one missing this flag set to FALSE

if (WIN32)
    #if (NOT AR2GEMS_SOURCE_PATH AND NOT AR2GEMS_BUILD_PATH)
        GET_FILENAME_COMPONENT(AR2GEMS_WINREGISTRY_PATH 
                               "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\SGeMS-ar2Tech-beta-x64;Path]"
                               ABSOLUTE CACHE)
    #endif (NOT AR2GEMS_SOURCE_PATH AND NOT AR2GEMS_BUILD_PATH)
endif(WIN32)

if (APPLE)
	# ???
	SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
elseif (UNIX)
	SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
elseif (WIN32)
	SET(CMAKE_FIND_LIBRARY_PREFIXES "")
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
endif (APPLE)

set(LIB_NAMES_RELEASE
    ar2gems_actions
    ar2gems_appli
    ar2gems_charts
    ar2gems_extragui
    ar2gems_filters
    ar2gems_geostat
    ar2gems_grid
    ar2gems_gui
    ar2gems_math
    ar2gems_qwt
    ar2gems_utils
    ar2gems_widgets  
)

set(LIB_NAMES_DEBUG 
    ar2gems_actions_d
    ar2gems_appli_d
    ar2gems_charts_d
    ar2gems_extragui_d
    ar2gems_filters_d
    ar2gems_geostat_d
    ar2gems_grid_d
    ar2gems_gui_d
    ar2gems_math_d
    ar2gems_qwt_d
    ar2gems_utils_d
    ar2gems_widgets_d
)


set(LIB_RELEASE_SEARCH_PATHES
${AR2GEMS_BUILD_PATH}/Release/lib # UNIX
${AR2GEMS_BUILD_PATH}/lib/Release # VS2010
${AR2GEMS_WINREGISTRY_PATH}
/usr/lib64
/usr/lib
/usr/local/lib64
/usr/local/lib
/sw/lib
/opt/local/lib
)

set(LIB_DEBUG_SEARCH_PATHES
${AR2GEMS_BUILD_PATH}/Debug/lib # UNIX
${AR2GEMS_BUILD_PATH}/lib/Debug # VS2010
${AR2GEMS_WINREGISTRY_PATH}
/usr/lib64
/usr/lib
/usr/local/lib64
/usr/local/lib
/sw/lib
/opt/local/lib
)

set(HEADER_SEARCH_PATHES
${AR2GEMS_SOURCE_PATH}/
${AR2GEMS_PATH}/include/
${AR2GEMS_WINREGISTRY_PATH}/include/
/usr/include
/usr/local/include
/sw/include
/opt/local/include
)
    
        
MACRO(FindAR2GEMS)
    if (FINDAR2GEMS_DEBUG)
        message(STATUS "AR2GEMS path: ${AR2GEMS_PATH}")
        message(STATUS "AR2GEMS winregistry path: ${AR2GEMS_WINREGISTRY_PATH}")
    endif ()
    
    find_path(AR2GEMS_INCLUDE_DIR ar2gems/sgems_version.h
        ${HEADER_SEARCH_PATHES} NO_DEFAULT_PATH
        DOC "The directory where ar2gems/sgems_version.h resides")
    list(APPEND AR2GEMS_INCLUDE_DIRS ${AR2GEMS_INCLUDE_DIR})
                  
    if (FINDAR2GEMS_DEBUG)
        message("includes: ${AR2GEMS_INCLUDE_DIRS}")
    endif(FINDAR2GEMS_DEBUG)
     
    # search RELEASE                   
    foreach(RELEASE_LIB ${LIB_NAMES_RELEASE})
        if (FINDAR2GEMS_DEBUG)
            message("Searching release lib: ${RELEASE_LIB}")
        endif()
        
        find_library(SEARCH_${RELEASE_LIB} ${RELEASE_LIB} 
            PATHS ${LIB_RELEASE_SEARCH_PATHES} NO_DEFAULT_PATH)
                
        if (${SEARCH_${RELEASE_LIB}} MATCHES SEARCH_${RELEASE_LIB}-NOTFOUND)
            set(AR2GEMS_ALL_RELEASE_LIBS_FOUND FALSE)
            message("Release lib NOT found: ${RELEASE_LIB}")
        else()
            list(APPEND AR2GEMS_RELEASE_LIBRARIES ${SEARCH_${RELEASE_LIB}})  
            list(APPEND AR2GEMS_LIBRARIES optimized ${SEARCH_${RELEASE_LIB}})        
        endif ()
    endforeach()  

    # search DEBUG  
    foreach(DEBUG_LIB ${LIB_NAMES_DEBUG})
        if (FINDAR2GEMS_DEBUG)
            message("Searching debug lib: ${DEBUG_LIB}")
        endif()
        
        find_library(SEARCH_${DEBUG_LIB} ${DEBUG_LIB} 
            PATHS ${LIB_DEBUG_SEARCH_PATHES} NO_DEFAULT_PATH)

        if (${SEARCH_${DEBUG_LIB}} MATCHES SEARCH_${DEBUG_LIB}-NOTFOUND)
            set(AR2GEMS_ALL_DEBUG_LIBS_FOUND FALSE)
            message("Debug lib NOT found: ${DEBUG_LIB}")
        else()
            list(APPEND AR2GEMS_DEBUG_LIBRARIES ${SEARCH_${DEBUG_LIB}})
            list(APPEND AR2GEMS_LIBRARIES debug ${SEARCH_${DEBUG_LIB}})
        endif ()
    endforeach() 
        
    if(AR2GEMS_INCLUDE_DIRS AND AR2GEMS_ALL_RELEASE_LIBS_FOUND)
        set(AR2GEMS_RELEASE_FOUND TRUE)
        message(STATUS "Found Release AR2GEMS library ${AR2GEMS_RELEASE_LIBRARIES}")
        message(STATUS "Found Release AR2GEMS includes ${AR2GEMS_INCLUDE_DIRS}")
    else()
        set(AR2GEMS_RELEASE_FOUND FALSE)
        message(STATUS "Release AR2GEMS not found. Specify AR2GEMS_BUILD_PATH (needed for lib) and AR2GEMS_SOURCE_PATH (needed for headers) to locate it")
    endif()

    if(AR2GEMS_INCLUDE_DIRS AND AR2GEMS_ALL_DEBUG_LIBS_FOUND)
        set(AR2GEMS_DEBUG_FOUND TRUE)
        message(STATUS "Found Debug AR2GEMS library ${AR2GEMS_DEBUG_LIBRARIES}")
        message(STATUS "Found Debug AR2GEMS includes ${AR2GEMS_INCLUDE_DIRS}")
    else()    
        set(AR2GEMS_DEBUG_FOUND FALSE)
        message(STATUS "Debug AR2GEMS not found. Specify AR2GEMS_BUILD_PATH (needed for lib) and AR2GEMS_SOURCE_PATH (needed for headers) to locate it")   
    endif()
    
    if (AR2GEMS_RELEASE_FOUND OR AR2GEMS_DEBUG_FOUND)
		set(AR2GEMS_FOUND TRUE)
	else()
		set(AR2GEMS_FOUND FALSE)
	endif()	
    
ENDMACRO()

