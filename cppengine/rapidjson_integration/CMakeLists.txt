cmake_minimum_required(VERSION 3.24)

if(ENGINE_JSON_INTEGRATION_RAPIDJSON)

message(STATUS "rapidjson integration library selected")

FetchContent_Declare(
        rapidjson
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        GIT_TAG        master
        SOURCE_SUBDIR  does-not-exist
)

FetchContent_MakeAvailable(rapidjson)

add_library(rapidjson INTERFACE)
target_include_directories(rapidjson INTERFACE ${rapidjson_SOURCE_DIR}/include)

set(INTEGRATION_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INTEGRATION_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${ENGINE_JSON_INTROSPECTION_INTEGRATION_TARGET} OBJECT
    ${INTEGRATION_SRC_DIR}/rapidjson_json_serialiser.cpp
    ${INTEGRATION_SRC_DIR}/rapidjson_json_deserialiser.cpp
)

target_include_directories(${ENGINE_JSON_INTROSPECTION_INTEGRATION_TARGET} PUBLIC ${INTEGRATION_INC_DIR})
target_precompile_headers(${ENGINE_JSON_INTROSPECTION_INTEGRATION_TARGET} PUBLIC ${INTEGRATION_INC_DIR}/rapidjson_integration.hpp)
target_link_libraries(${ENGINE_JSON_INTROSPECTION_INTEGRATION_TARGET} PUBLIC rapidjson ${ENGINE_TARGET})
add_dependencies(${ENGINE_JSON_INTROSPECTION_INTEGRATION_TARGET} ${ENGINE_TARGET})

set_property(GLOBAL PROPERTY ENGINE_JSON_INTROSPECTION_INTEGRATION_LINKED 1)

endif()