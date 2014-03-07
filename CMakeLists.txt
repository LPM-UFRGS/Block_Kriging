cmake_minimum_required(VERSION 2.8)


set(PROJECT_NAME LPM_UFRGS_Block_Kriging)

project(${PROJECT_NAME})


######################################################################
# Please set the variables with your preferences. The defaults should
# work out of the box.
######################################################################


if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING
       "Choose the type of build, options are: Debug Release"
       FORCE )
endif()

set(ALLOW_BUILD_PACKAGE 0 CACHE TYPE BOOL)

if (APPLE)
     # ...
elseif (UNIX)
    #set(BOOST_ROOT "E:/workspace/ar2externals/Boost/win64/release-V1.49.0-VC2010" CACHE TYPE STRING)
    #set(VTK_DIR "D:/workspace/VTK-master/build" CACHE TYPE STRING)
    set(AR2GEMS_SOURCE_PATH "/home/balda/workspace/freelancejob/AlexSanto/ar2gems" CACHE TYPE STRING)
    set(AR2GEMS_BUILD_PATH "/home/balda/workspace/freelancejob/AlexSanto/ar2gems_build" CACHE TYPE STRING)
elseif (WIN32)
    set(BOOST_ROOT "d:/release-V1.49.0-VC2010" CACHE TYPE STRING)
    set(VTK_DIR "D:/workspace/VTK-master/build" CACHE TYPE STRING)
    #set(AR2GEMS_PATH "c:/SGeMS-ar2tech-x64" CACHE TYPE STRING) # if commented the searching happens by registry information
    set(AR2GEMS_SOURCE_PATH "d:/workspace/ar2gems" CACHE TYPE STRING)
    set(AR2GEMS_BUILD_PATH "d:/workspace/ar2gems_build" CACHE TYPE STRING)
endif (APPLE)

# SET RELEVANT VARS FOR PACKAGE
if (ALLOW_BUILD_PACKAGE)
	if (APPLE)
	elseif (UNIX)
	    SET(PACKAGE_TYPE "DEB")    # DEB or RPM
	endif (APPLE)
	
	SET(PACKAGE_MAINTAINER "Alex Santo <asanto@stereoofusion.com>")
	#SET(PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/about.txt")
	#SET(PACKAGE_LICENSE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE-ar2tech.txt")
	    
	SET(PACKAGE_VERSION_MAJOR "1")
	SET(PACKAGE_VERSION_MINOR "0")
	SET(PACKAGE_VERSION_PATCH "0")
	    
	SET(PACKAGE_SYSTEM_NAME "amd64")
endif (ALLOW_BUILD_PACKAGE)

if (APPLE)
     # ...
elseif (UNIX)
    set(INSTALL_LIB_DIR "/usr/bin/plugins/designer")
elseif (WIN32)
    SET(INSTALL_LIB_DIR         "../../../../plugins/designer") # don't set ABS path it will fail at stage of package creation (ABS path forbiden)
    SET(INSTALL_GEOSTAT_LIB_DIR "../../../../plugins/Geostat") # don't set ABS path it will fail at stage of package creation (ABS path forbiden)
    
    SET(PACKAGE_DIR         "../../../plugins/") # don't set ABS path it will fail at stage of package creation (ABS path forbiden)
endif (APPLE)

if ( MSVC )
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${AR2GEMS_BUILD_PATH}/bin/Debug/plugins/Geostat )
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${AR2GEMS_BUILD_PATH}/bin/Release/plugins/Geostat )
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${AR2GEMS_BUILD_PATH}/bin/Debug/plugins/Geostat )
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${AR2GEMS_BUILD_PATH}/bin/Release/plugins/Geostat )	
endif ( MSVC )

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(AR2GEMS REQUIRED)
FindAR2GEMS()
if (AR2GEMS_FOUND)
	include_directories(${AR2GEMS_INCLUDE_DIRS}/ar2gems)
	include_directories(${AR2GEMS_INCLUDE_DIRS}/ar2GsTL)
    include_directories(${AR2GEMS_INCLUDE_DIRS})
endif ()

if (AR2GEMS_BUILD_PATH)
    #include automatic generated ui_*.h headers
	include_directories(${AR2GEMS_BUILD_PATH}/ar2gems)
endif ()

include_directories()
     


### Enabling Boost ###################################################
FIND_PACKAGE(Boost REQUIRED )
# Uncomment if Boost isn't in your path:
set(Boost_NO_SYSTEM_PATHS TRUE)
FIND_PACKAGE( Boost REQUIRED )
if(Boost_FOUND)
  message(STATUS "Boost found in ${BOOST_ROOT}")
  include_directories(${Boost_INCLUDE_DIRS})
endif()


######################################################################
############### DON'T NEED CHANGE ANYTHING HERE ######################
######################################################################

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -march=native")
  set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -ggdb -march=native")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "/MP4")
  # customize flags for Visual Studio
endif()

### Enabling Qt4 #####################################################
find_package(Qt4 REQUIRED COMPONENTS
             QtCore QtGui QtXml QtSvg QtDesigner QtUiTools)
if(QT4_FOUND)
  message(STATUS "Qt4 found in ${QT_INCLUDE_DIR}")
  include(${QT_USE_FILE})
endif()

### Enabling VTK #####################################################
#find_package(VTK REQUIRED)
find_package(VTK COMPONENTS REQUIRED
  vtkCommonCore
  vtkFiltersSources
  vtkRenderingCore
  vtkRenderingOpenGL
  vtkInteractionStyle
  vtkChartsCore
  vtkRenderingFreeTypeOpenGL
  vtkIOXML  
  vtkRenderingQt
  vtkGUISupportQt
  vtkViewsQt
  vtkViewsContext2D
  vtkInteractionWidgets
)
  
if(VTK_FOUND)
  message(STATUS "VTK found in ${VTK_DIR}")
  include(${VTK_USE_FILE})
endif()

### Enabling Python ##################################################
find_package(PythonLibs 2.7 REQUIRED)
if(PYTHONLIBS_FOUND)
  message(STATUS "Python found in ${PYTHON_INCLUDE_DIR}")
  include_directories(${PYTHON_INCLUDE_DIR})
endif()


# Process all headers with Q_OBJECT
QT4_WRAP_CPP(${PROJECT_NAME}_MOC

)

## File to compile
add_library(${PROJECT_NAME} SHARED
LPM_UFRGS_Block_Kriging.cpp
LPM_UFRGS_Block_Kriging.h

Covariance_Point_Point.h
Covariance_Point_Point.cpp

Covariance_Block_Block.h
Covariance_Block_Block.cpp

Covariance_Point_Block.h
Covariance_Point_Block.cpp

Build_LHS_Covariance_Matrix.h
Build_LHS_Covariance_Matrix.cpp

Build_RHS_Covariance_Matrix.h
Build_RHS_Covariance_Matrix.cpp

Solve_Kriging_System.h
Solve_Kriging_System.cpp

Calculate_Estimates.h
Calculate_Estimates.cpp

common.h
library_init.cpp

  ${${PROJECT_NAME}_MOC}
#  ${${PROJECT_NAME}_FORMS}
)

target_link_libraries(${PROJECT_NAME}
  ${AR2GEMS_LIBRARIES}
  ${QT_LIBRARIES}
  ${VTK_LIBRARIES}
)

source_group(Qt FILES ${${PROJECT_NAME}_MOC} )

if (WIN32)
  add_definitions(-DPLUGINS_EXPORT)
endif()



INSTALL(TARGETS ${PROJECT_NAME} DESTINATION "${INSTALL_LIB_DIR}")

   
# CREATE PACKAGE    
if (ALLOW_BUILD_PACKAGE)
    # COMMON    
    SET(CPACK_DEBIAN_PACKAGE_MAINTAINER ${PACKAGE_MAINTAINER})
    
    SET(CPACK_PACKAGE_DESCRIPTION_FILE ${PACKAGE_DESCRIPTION_FILE})
    SET(CPACK_RESOURCE_FILE_LICENSE ${PACKAGE_LICENSE_FILE})
    
    SET(CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION_MAJOR})
    SET(CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION_MINOR})
    SET(CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION_PATCH})
    
    SET(CPACK_SYSTEM_NAME ${PACKAGE_SYSTEM_NAME})
        	                          
	if (APPLE)
	    # ...
	elseif (UNIX)
	    # DEB SPECIFIC
	    if (PACKAGE_TYPE STREQUAL "DEB")
	        SET(CPACK_GENERATOR "DEB")
	        SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON) # autogenerate dependency information (package d-shlibs should be installed)
	        SET(CPACK_DEBIAN_PACKAGE_DEPENDS "ar2gems (>= 1.0.0)")
	    endif (PACKAGE_TYPE STREQUAL "DEB")
	    
	    # RPM SPECIFIC
	    if (PACKAGE_TYPE STREQUAL "RPM")
	        SET(CPACK_GENERATOR "RPM")
	    
	    endif(PACKAGE_TYPE STREQUAL "RPM")
	              
	elseif (WIN32)
		set(CPACK_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
	    set(CPACK_GENERATOR "NSIS")
	    
		set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME})
		set(CPACK_NSIS_INSTALLER_OUTFILE_NAME ${CPACK_PACKAGE_FILE_NAME})
    	 
        #pass NATIVE PATHS to NSIS template
		string(REPLACE "/" "\\\\" WINNATIVE_PACKAGE_DIR ${PACKAGE_DIR})
	    set(CPACK_NSIS_AR2GEMS_PLUGIN_BINARY_DIR ${WINNATIVE_PACKAGE_DIR})
            
	endif (APPLE)
    
    INCLUDE(CPack)
        	
endif (ALLOW_BUILD_PACKAGE)
  
  
