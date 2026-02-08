cmake_minimum_required(VERSION 3.24)
project(cppgame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPP_GAME_ENGINE_NOT_LINKED 1)
set(CPP_GAME_INTEGRATION_NOT_LINKED 1)

set(CPP_GAME_ENGINE)
set(CPP_GAME_INTEGRATION)

add_subdirectory("${CMAKE_SOURCE_DIR}/engine/")
add_subdirectory("${CMAKE_SOURCE_DIR}/raylib_integraion/")
add_subdirectory("${CMAKE_SOURCE_DIR}/game")

# ─── Demo Application ────────────────────────────────────────────────────────
add_executable(demo src/main.cpp)
target_link_libraries(demo PRIVATE engine raylib_integration)
