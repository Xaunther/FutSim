# Core source files
SET(FUTSIM_CORE_SOURCE
	src/IJsonable.cpp
	src/NationalityUtils.cpp
)

# Football source files
SET(FUTSIM_FOOTBALL_SOURCE
	src/football/CPlayerSkills.cpp
)

# Core internal headers
SET(FUTSIM_CORE_INTERNAL_HEADERS
	src/NationalityConversionMaps.h
)

# Football internal headers
SET(FUTSIM_FOOTBALL_INTERNAL_HEADERS)

# Core external headers
SET(FUTSIM_CORE_EXTERNAL_HEADERS
	include/Config.h
	include/ENationality.h
	include/ExceptionUtils.h
	include/FutSim.h
	include/IJsonable.h
	include/IJsonableTypes.h
	include/NationalityUtils.h
)

# Football external headers
SET(FUTSIM_FOOTBALL_EXTERNAL_HEADERS
	include/football/CPlayerSkills.h
	include/football/CPlayerSkillsTypes.h
)

# Source files
SET(FUTSIM_SOURCE
	${FUTSIM_CORE_SOURCE}
	${FUTSIM_FOOTBALL_SOURCE}
)

# Internal headers
SET(FUTSIM_INTERNAL_HEADERS
	${FUTSIM_CORE_INTERNAL_HEADERS}
	${FUTSIM_FOOTBALL_INTERNAL_HEADERS}
)

# External headers
SET(FUTSIM_EXTERNAL_HEADERS
	${FUTSIM_CORE_EXTERNAL_HEADERS}
	${FUTSIM_FOOTBALL_EXTERNAL_HEADERS}
)