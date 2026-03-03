cmake_minimum_required(VERSION 3.24)
project(cppgame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cppengine)

get_property(ENGINE_LIB GLOBAL PROPERTY CPP_GAME_ENGINE_LIB)

if("${ENGINE_LIB}" STREQUAL "")
    message(FATAL_ERROR "essential libraries could not be linked, please check settings.")
else()
set(CPP_GAME_ASSET_FOLDER_NAME assets)
set(CPP_GAME_TARGET_NAME)
set(CPP_GAME_ASSET_PHYS_LOCATION)
set(CPP_GAME_ASSET_LINK_LOCATION)

add_subdirectory("${CMAKE_SOURCE_DIR}/game")

add_executable(${CMAKE_PROJECT_NAME} $<TARGET_OBJECTS:${CPP_GAME_TARGET_NAME}>)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CPP_GAME_TARGET_NAME})

add_custom_target(
        link_assets
        COMMAND ${CMAKE_COMMAND}
        -DALWAYS_COPY=FALSE
        -DASSET_SRC_LOCATION="${CPP_GAME_ASSET_PHYS_LOCATION}"
        -DASSET_SYMLINK_LOCATION="${CPP_GAME_ASSET_LINK_LOCATION}/${CPP_GAME_ASSET_FOLDER_NAME}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/postbuild.cmake"
        COMMENT "creating assets folder for target"
)
add_dependencies(${CMAKE_PROJECT_NAME} ${CPP_GAME_TARGET_NAME} link_assets)
endif()