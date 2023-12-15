cmake_minimum_required(VERSION 3.22)

# Parent project name
set(PARENT_PROJECT_NAME ${PROJECT_NAME})

# Project for tests
project(Tests LANGUAGES CXX)

include(FileList.cmake)

# Include directories
include_directories(${FUTSIM_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

# Link directories
link_directories(${FUTSIM_LIBS_DIR})

# For every test source add corresponding test
function(add_futsim_test MODULE_NAME)
	foreach(TEST_SOURCE ${FUTSIM_TESTS_UNIT_${MODULE_NAME}_SOURCE})
		string(REPLACE ".cpp" "" TEST_NAME ${TEST_SOURCE})
		get_filename_component(TEST_NAME ${TEST_NAME} NAME)
		add_executable(${TEST_NAME} ${FUTSIM_${FUTSIM_MODULE}_OBJECTS} ${TEST_SOURCE} ${FUTSIM_TESTS_ENGINE_SOURCE})
		add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
	endforeach()
endfunction()

foreach(FUTSIM_MODULE ${FUTSIM_MODULES})
	add_futsim_test(${FUTSIM_MODULE})
endforeach(FUTSIM_MODULE)
