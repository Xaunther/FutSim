cmake_minimum_required(VERSION 3.22)

# Check if doxygen is installed
find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
	message(FATAL_ERROR "Doxygen not found. Install it or set turn BUILD_DOCUMENTATION off.")
endif()

# Set input and output files
set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Configure doxyfile
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

# Add target
add_custom_target(doc_doxygen ALL
	COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating documentation with Doxygen"
	VERBATIM)