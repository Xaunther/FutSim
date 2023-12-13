cmake_minimum_required(VERSION 3.22)

# FutSim project data
project(FutSim VERSION 0.1 DESCRIPTION "A football command-line simulator" HOMEPAGE_URL "https://github.com/Xaunther/FutSim" LANGUAGES CXX)

# C++ 20 required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Option to build documentation
option(BUILD_DOCUMENTATION "Rule to build documentation" true)

# Option to build tests
option(BUILD_TESTS "Rule to build tests" true)

# Names of relevant directories
set(FUTSIM_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FUTSIM_BINARY_DIR ${FUTSIM_DIR}/bin)
set(FUTSIM_INCLUDE_DIR ${FUTSIM_DIR}/include)
set(FUTSIM_LIBS_DIR ${FUTSIM_DIR}/lib)

# Default build is "release"
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_COMPILER_IS_GNUCC CACHE STRING "Choose the build type (Debug, Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -Os")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "-W4 -WX -EHsc -Os")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-Os")

# Find json package
set(JSON_DIR ${FUTSIM_DIR}/externals/json)
add_subdirectory(${JSON_DIR})

# Function to add a new object module
function(add_futsim_object_module MODULE_NAME SOURCES)
	add_Library(${MODULE_NAME}Objects OBJECT ${SOURCES} ${ARGN})
	set_target_properties(${MODULE_NAME}Objects PROPERTIES
		POSITION_INDEPENDENT_CODE true
		ARCHIVE_OUTPUT_DIRECTORY ${FUTSIM_LIBS_DIR}
		LIBRARY_OUTPUT_DIRECTORY ${FUTSIM_LIBS_DIR}
		RUNTIME_OUTPUT_DIRECTORY ${FUTSIM_LIBS_DIR})
	message(STATUS "Added object module ${MODULE_NAME}")
endfunction()

# Function to add a new module
function(add_futsim_module MODULE_NAME MODULE_TYPE SOURCES)
	if(MODULE_TYPE STREQUAL SHARED)
		set(MODULE_SUFFIX "Shared")
	elseif(MODULE_TYPE STREQUAL STATIC)
		set(MODULE_SUFFIX "Static")
	else()
		message(FATAL_ERROR "Module type ${MODULE_TYPE} not recognized. Only 'STATIC' and 'SHARED' are allowed.")
	endif()

	add_Library(${MODULE_NAME}${MODULE_SUFFIX} ${MODULE_TYPE} ${SOURCES} ${ARGN})
	set_target_properties(${MODULE_NAME}${MODULE_SUFFIX} PROPERTIES
		POSITION_INDEPENDENT_CODE true
		ARCHIVE_OUTPUT_DIRECTORY ${FUTSIM_LIBS_DIR}
		LIBRARY_OUTPUT_DIRECTORY ${FUTSIM_LIBS_DIR}
		RUNTIME_OUTPUT_DIRECTORY ${FUTSIM_LIBS_DIR})
	target_link_libraries(${MODULE_NAME}${MODULE_SUFFIX} PRIVATE nlohmann_json::nlohmann_json)
	message(STATUS "Added ${MODULE_TYPE} module ${MODULE_NAME}")
endfunction()

# List of source files
include(FileList.cmake)

# Add configuration files
configure_file(${FUTSIM_INCLUDE_DIR}/Config.h.in ${FUTSIM_INCLUDE_DIR}/Config.h)

foreach(HEADER ${FUTSIM_EXTERNAL_HEADERS})
	string(REGEX REPLACE "include/" "" HEADER ${HEADER})
	set(INCLUDE_FUTSIM_EXTERNAL_HEADERS "${INCLUDE_FUTSIM_EXTERNAL_HEADERS}#include \"${HEADER}\"\n")
endforeach()

configure_file(${FUTSIM_INCLUDE_DIR}/FutSim.h.in ${FUTSIM_INCLUDE_DIR}/FutSim.h)

# Include directories
include_directories(${FUTSIM_INCLUDE_DIR} ${FUTSIM_DIR}/src ${JSON_DIR}/include)

# Link directories
link_directories(${FUTSIM_LIBS_DIR})

# Build FutSim
add_futsim_object_module(${PROJECT_NAME}Core "${FUTSIM_CORE_SOURCE}")
set(FUTSIM_CORE_OBJECTS $<TARGET_OBJECTS:${PROJECT_NAME}CoreObjects>)
set(FUTSIM_OBJECTS ${FUTSIM_CORE_OBJECTS})

# Final build step. All objects must have been appended to FUTSIM_OBJECTS.
add_futsim_module(${PROJECT_NAME}Core STATIC ${FUTSIM_OBJECTS})

if(LIB_FUTSIM_SHARED)
	add_futsim_module(${PROJECT_NAME}Core SHARED ${FUTSIM_OBJECTS})
endif()

# Build documentation
include(CTest)

if(BUILD_DOCUMENTATION)
	add_subdirectory(doc)
endif()

# Build tests
if(BUILD_TESTS)
	add_subdirectory(tests)
endif()
