PROJECT(loldog)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Set version.
SET(VERSION_MAJOR 1)
SET(VERSION_MINOR 1)
SET(VERSION_BUILD 0)

# Find Curses.
FIND_PACKAGE(Curses)
IF (NOT CURSES_FOUND)
    MESSAGE(FATAL_ERROR "Curses not found!")
ELSE  ()
    MESSAGE("Curses include directory: ${CURSES_INCLUDE_DIR}")
    MESSAGE("Curses libraries:         ${CURSES_LIBRARIES}")
ENDIF ()

# Make the config header.
MESSAGE("Creating ${CMAKE_CURRENT_BINARY_DIR}/config.h")
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
               "${CMAKE_CURRENT_BINARY_DIR}/config.h")

# Make the target.
INCLUDE_DIRECTORIES(${CURSES_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
ADD_EXECUTABLE(loldog linelist.c lol.c main.c options.c utils.c)
TARGET_LINK_LIBRARIES(loldog ${CURSES_LIBRARIES})
INSTALL(TARGETS loldog DESTINATION bin)

