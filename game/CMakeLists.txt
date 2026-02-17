cmake_minimum_required(VERSION 3.24)

set(GAME_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GAME_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(demo
        ${GAME_SRC_DIR}/test_level.cpp
        ${GAME_SRC_DIR}/main.cpp
)
target_link_libraries(demo PRIVATE ${CPP_GAME_ENGINE} ${CPP_GAME_INTEGRATION})

target_include_directories(demo PUBLIC ${GAME_INC_DIR})
target_precompile_headers(demo PUBLIC ${GAME_INC_DIR}/game.hpp)