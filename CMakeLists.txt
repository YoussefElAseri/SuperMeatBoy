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
SET(SRC Representation/ResourceIdentifiers.h Representation/Game.cpp Representation/GoalView.cpp Representation/GoalView.h
        Representation/Game.h Logic/World.cpp Logic/World.h Logic/Stopwatch.cpp Logic/Stopwatch.h Logic/Subject.cpp
        Logic/Subject.h Logic/Observer.h Logic/Camera.cpp Logic/Camera.h Logic/AbstractEntityFactory.h
        Representation/ConcretePlayerFactory.cpp Representation/ConcretePlayerFactory.h Representation/WallView.cpp
        Representation/WallView.h Representation/ConcreteWallFactory.cpp Representation/ConcreteWallFactory.h
        Representation/ConcreteGoalFactory.cpp Representation/ConcreteGoalFactory.h Representation/EntityView.cpp
        Representation/EntityView.h Logic/EntityModel.cpp Logic/EntityModel.h Representation/main.cpp Logic/Player.cpp
        Logic/Player.h Logic/Wall.cpp Logic/Wall.h Logic/Goal.cpp Logic/Goal.h Representation/PlayerView.cpp
        Representation/PlayerView.h Logic/AbstractPlayerFactory.h Representation/StateManager.cpp
        Representation/StateManager.h Representation/State.h Representation/MenuState.cpp Representation/MenuState.h
        Representation/LevelState.cpp Representation/LevelState.h Logic/Rectangle.h
        Representation/ConcreteFireFactory.cpp Representation/ConcreteFireFactory.h Logic/Fire.cpp Logic/Fire.h
        Representation/FireView.cpp Representation/FireView.h)

# The program we're compiling with the sources set above
ADD_EXECUTABLE(SuperMeatBoy ${SRC})

# Link target to SFML libs
TARGET_LINK_LIBRARIES(SuperMeatBoy sfml-system sfml-graphics sfml-window)

set(CMAKE_CXX_STANDARD 20)

# Install our executable to the CMAKE_INSTALL_PREFIX/bin
INSTALL(TARGETS SuperMeatBoy DESTINATION bin)
