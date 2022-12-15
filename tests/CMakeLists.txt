cmake_minimum_required( VERSION 3.22 )

# Project for tests
project( Tests LANGUAGES CXX )

include( FileList.cmake )

# Include directories
include_directories( ${FUTSIM_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src )

# Link directories
link_directories(${FUTSIM_LIBS_DIR} )

# For every test source add corresponding test
foreach(TEST_SOURCE ${FUTSIM_TESTS_UNIT_SOURCE})
	string( REPLACE ".cpp" "" TEST_NAME TEST_SOURCE )
	add_executable( ${TEST_NAME} ${TEST_SOURCE} )
	add_test( NAME ${TEST_NAME} COMMAND ${TEST_NAME} )
endforeach()
