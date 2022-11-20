cmake_minimum_required(VERSION 3.20)
project(SuperMeatBoy)

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

# Add include dirs for SFML
INCLUDE_DIRECTORIES(SFML-2.5.1/include)

# The source files to compile
SET(SRC main.cpp Game.cpp Game.h Stopwatch.cpp Stopwatch.h World.cpp World.h Camera.cpp Camera.h)

# The program we're compiling with the sources set above
ADD_EXECUTABLE(SuperMeatBoy ${SRC})

# Link target to SFML libs
TARGET_LINK_LIBRARIES(SuperMeatBoy sfml-system sfml-graphics sfml-window)

set(CMAKE_CXX_STANDARD 20)

# Install our executable to the CMAKE_INSTALL_PREFIX/bin
INSTALL(TARGETS SuperMeatBoy DESTINATION bin)
