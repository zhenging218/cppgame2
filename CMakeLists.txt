cmake_minimum_required(VERSION 3.24)
project(cppgame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INTEGRATION_API "GLFW_GLAD")
set(ASSET_IMAGE_LOADER_API "STB")

set(CPP_GAME_ENGINE_NOT_LINKED 1)
set(CPP_GAME_INTEGRATION_NOT_LINKED 1)
set(CPP_GAME_ASSET_IMAGE_LOADER_NOT_LINKED 1)

set(CPP_GAME_ENGINE)
set(CPP_GAME_INTEGRATION)
set(CPP_GAME_ASSET_IMAGE_LOADER)

add_subdirectory("${CMAKE_SOURCE_DIR}/engine/")
add_subdirectory("${CMAKE_SOURCE_DIR}/glfw_glad_integration/")
add_subdirectory("${CMAKE_SOURCE_DIR}/stb_asset_integration/")

if(${CPP_GAME_ENGINE_NOT_LINKED} OR ${CPP_GAME_INTEGRATION_NOT_LINKED} OR ${CPP_GAME_ASSET_IMAGE_LOADER_NOT_LINKED})
    message(FATAL_ERROR "essential libraries could not be linked, please check settings.")
else()
set(CPP_GAME_ASSET_FOLDER_NAME assets)
set(CPP_GAME_TARGET_NAME)
set(CPP_GAME_ASSET_LOCATION)
add_subdirectory("${CMAKE_SOURCE_DIR}/game")

add_custom_target(
        link_assets
        COMMAND ${CMAKE_COMMAND}
        -DASSET_SRC_LOCATION="${CPP_GAME_ASSET_LOCATION}"
        -DASSET_SYMLINK_LOCATION="${CMAKE_CURRENT_BINARY_DIR}/${CPP_GAME_TARGET_NAME}/${CPP_GAME_ASSET_FOLDER_NAME}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/postbuild.cmake"
        COMMENT "creating assets folder for target"
)
add_dependencies(${CPP_GAME_TARGET_NAME} link_assets)
endif()