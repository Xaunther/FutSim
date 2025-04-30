file( READ "${VERSION_FILE}" FUTSIM_VERSION )
configure_file(${SRC} ${DST} @ONLY)
