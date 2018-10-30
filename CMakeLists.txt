cmake_minimum_required (VERSION 2.6)
project (SBNfit)


FIND_PACKAGE(ROOT)# COMPONENTS Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread)

if(ROOT_FOUND)
	message("Found ROOT using CMAKE FIND_PACKAGE")
	include(${ROOT_USE_FILE})
ELSE()
	message("ROOT not compiled using CMAKE, use root-config")
	#Get our ROOT libraries and such
	FIND_PROGRAM(ROOT_CONFIG root-config)
	EXEC_PROGRAM(${ROOT_CONFIG} ARGS --cflags --glibs OUTPUT_VARIABLE ROOT_CXX_FLAGS)
	message("ROOT cxx flags set to: ${ROOT_CXX_FLAGS}")
ENDIF()

#Get our GSL libraries
FIND_PROGRAM(GSL_CONFIG gsl-config)
EXEC_PROGRAM(${GSL_CONFIG} ARGS --cflags OUTPUT_VARIABLE GSL_CXX_FLAGS)
EXEC_PROGRAM(${GSL_CONFIG} ARGS --libs OUTPUT_VARIABLE GSL_LIBS)

set (CMAKE_SO_CXX_FLAGS " ${ROOT_CXX_FLAGS} ${GSL_LIBS} ${GSL_CXX_FLAGS} ${CMAKE_CXX_FLAGS} -w -Wno-deprecated-declarations")

set (CMAKE_CXX_FLAGS "${CMAKE_SO_CXX_FLAGS}")

include_directories(${PROJECT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable (rantest rantest.cxx)
target_link_libraries(rantest  ${ROOT_LIBRARIES} gsl gslcblas ${GSL_LIBRARIES})


