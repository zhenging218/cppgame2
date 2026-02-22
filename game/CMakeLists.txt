cmake_minimum_required(VERSION 3.24)

set(GAME_TARGET_NAME demo)

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

add_custom_command(TARGET demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${GAME_TARGET_NAME}>/assets"
    COMMENT "creating symlink for assets folder ${CMAKE_CURRENT_SOURCE_DIR}/assets <-> $<TARGET_FILE_DIR:${GAME_TARGET_NAME}>/assets"
)