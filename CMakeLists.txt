cmake_minimum_required( VERSION 3.25 )

# FutSim project data
project( FutSim VERSION 0.1 DESCRIPTION "A football command-line simulator" HOMEPAGE_URL "https://github.com/Xaunther/FutSim" LANGUAGES CXX )

# C++ 20 required
set( PROPERTIES CXX_STANDARD 20 )
set( PROPERTIES CXX_STANDARD_REQUIRED true )

# Option to build documentation
option( BUILD_DOCUMENTATION "Rule to build documentation" true )
# Option to build tests
option( BUILD_TESTS "Rule to build tests" true )

# Names of relevant directories
set( FUTSIM_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( FUTSIM_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin )
set( FUTSIM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( FUTSIM_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib )

# Compiler-specific flags
if( CMAKE_COMPILER_IS_GNUCC )
	set( CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror" )
else()
	set( CMAKE_CXX_FLAGS "-W4 -EHsc" )
endif()
set( CMAKE_CXX_FLAGS_RELEASE "-Os" )

# List of source files
include( FileList.cmake )

# Include directories
include_directories( ${FUTSIM_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src )

# Link directories
link_directories(${FUTSIM_LIBS_DIR} )

include( CTest )
if( BUILD_DOCUMENTATION )
	add_subdirectory( doc )
endif()

if( BUILD_TESTS )
	add_subdirectory( tests )
endif()
