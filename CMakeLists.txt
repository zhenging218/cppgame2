cmake_minimum_required(VERSION 3.24)
project(cppgame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INTEGRATION_API "RAYLIB")

set(CPP_GAME_ENGINE_NOT_LINKED 1)
set(CPP_GAME_INTEGRATION_NOT_LINKED 1)

set(CPP_GAME_ENGINE)
set(CPP_GAME_INTEGRATION)

add_subdirectory("${CMAKE_SOURCE_DIR}/engine/")
add_subdirectory("${CMAKE_SOURCE_DIR}/raylib_integration/")

if(${CPP_GAME_ENGINE_NOT_LINKED} OR ${CPP_GAME_INTEGRATION_NOT_LINKED})
    message(FATAL_ERROR "essential libraries could not be linked, please check settings.")
else()
add_subdirectory("${CMAKE_SOURCE_DIR}/game")
endif()