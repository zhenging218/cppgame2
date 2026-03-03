cmake_minimum_required(VERSION 3.24)

if("${ASSET_IMAGE_LOADER_API}" STREQUAL "STB")

set(STB_LIB_NAME)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stb)

set(ENGINE_INC_DIR ${CMAKE_SOURCE_DIR}/engine/include)

set(STB_ASSET_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(STB_ASSET_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(stb_asset_integration STATIC
    ${STB_ASSET_SRC_DIR}/stb_assets.cpp
    ${STB_ASSET_SRC_DIR}/stb_image_handle.cpp
    ${STB_ASSET_SRC_DIR}/stb_image_context.cpp
)

target_include_directories(stb_asset_integration PUBLIC ${ENGINE_INC_DIR} ${STB_ASSET_INC_DIR})
target_link_libraries(stb_asset_integration PUBLIC ${STB_LIB_NAME})

set(CPP_GAME_ASSET_IMAGE_LOADER stb_asset_integration PARENT_SCOPE)
set(CPP_GAME_ASSET_IMAGE_LOADER_NOT_LINKED 0 PARENT_SCOPE)

endif()