if(GIT_EXECUTABLE)
	get_filename_component(SRC_DIR ${SRC} DIRECTORY)
	# Generate a git-describe version string from Git repository tags
	execute_process(
		COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
		WORKING_DIRECTORY ${SRC_DIR}
		OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
		RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	if(NOT GIT_DESCRIBE_ERROR_CODE)
		string(SUBSTRING ${GIT_DESCRIBE_VERSION} 1 -1 FUTSIM_VERSION)
		execute_process(COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --blue --bold "Build version ${FUTSIM_VERSION}")
	endif()
endif()

# Final fallback: Just use a bogus version string that is semantically older
# than anything else and spit out a warning to the developer.
if(NOT DEFINED FUTSIM_VERSION)
	set(FUTSIM_VERSION v0.0.0-unknown)
	message(WARNING "Failed to determine FUTSIM_VERSION from Git tags. Using default version \"${FUTSIM_VERSION}\".")
endif()

configure_file(${SRC} ${DST} @ONLY)
