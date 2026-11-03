cmake_minimum_required(VERSION 3.24)

get_property(ENGINE_LIB GLOBAL PROPERTY CPP_GAME_ENGINE_LIB)

set(GAME_TARGET_NAME demo)
set(GAME_ASSET_FOLDER_NAME game_assets)
set(GAME_ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${GAME_ASSET_FOLDER_NAME})

set(GAME_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GAME_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${GAME_TARGET_NAME} OBJECT
        ${GAME_SRC_DIR}/test_component.cpp
        ${GAME_SRC_DIR}/test_component_2.cpp
        ${GAME_SRC_DIR}/test_level.cpp
        ${GAME_SRC_DIR}/main.cpp
)

target_link_libraries(${GAME_TARGET_NAME} PRIVATE ${ENGINE_LIB})

target_include_directories(${GAME_TARGET_NAME} PUBLIC ${GAME_INC_DIR})
target_precompile_headers(${GAME_TARGET_NAME} PUBLIC ${GAME_INC_DIR}/game.hpp)

add_dependencies(${GAME_TARGET_NAME} ${ENGINE_LIB})

set_property(GLOBAL PROPERTY CPP_GAME_TARGET_NAME ${GAME_TARGET_NAME})
set_property(GLOBAL PROPERTY CPP_GAME_ASSET_PHYS_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/${GAME_ASSET_FOLDER_NAME})
