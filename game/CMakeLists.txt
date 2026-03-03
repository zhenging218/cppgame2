cmake_minimum_required(VERSION 3.24)

set(GAME_TARGET_NAME demo)

set(GAME_ASSET_FOLDER_NAME assets)
set(GAME_ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${GAME_ASSET_FOLDER_NAME})

set(GAME_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GAME_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${GAME_TARGET_NAME}
        ${GAME_SRC_DIR}/test_component.cpp
        ${GAME_SRC_DIR}/test_level.cpp
        ${GAME_SRC_DIR}/main.cpp
)
target_link_libraries(${GAME_TARGET_NAME} PRIVATE ${CPP_GAME_ENGINE} ${CPP_GAME_INTEGRATION})

target_include_directories(${GAME_TARGET_NAME} PUBLIC ${GAME_INC_DIR})
target_precompile_headers(${GAME_TARGET_NAME} PUBLIC ${GAME_INC_DIR}/game.hpp)

add_custom_command(
        TARGET ${GAME_TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -DASSET_DIR="${GAME_ASSET_DIR}"
            -DASSET_SYMLINK_LOCATION="${CMAKE_CURRENT_BINARY_DIR}/${GAME_ASSET_FOLDER_NAME}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/game_postbuild.cmake"
        COMMENT "creating symlink to assets folder"
)