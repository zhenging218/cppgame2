cmake_minimum_required(VERSION 3.24)

if(ENGINE_ASSET_INTEGRATION_STB)

message(STATUS "STB Asset integration library selected")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stb)
get_property(STB_LIB_NAME GLOBAL PROPERTY STB_LIB_NAME)

set(STB_ASSET_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(STB_ASSET_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${ENGINE_ASSET_INTEGRATION_TARGET} OBJECT
    ${STB_ASSET_SRC_DIR}/stb_assets.cpp
    ${STB_ASSET_SRC_DIR}/stb_image_handle.cpp
    ${STB_ASSET_SRC_DIR}/stb_image_context.cpp
)

target_include_directories(${ENGINE_ASSET_INTEGRATION_TARGET} PUBLIC ${STB_ASSET_INC_DIR})
target_link_libraries(${ENGINE_ASSET_INTEGRATION_TARGET} PUBLIC ${STB_LIB_NAME} ${ENGINE_TARGET})
add_dependencies(${ENGINE_ASSET_INTEGRATION_TARGET} ${STB_LIB_NAME} ${ENGINE_TARGET})

set_property(GLOBAL PROPERTY ENGINE_ASSET_INTEGRATION_LINKED 1)

endif()