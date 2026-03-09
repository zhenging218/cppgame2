cmake_minimum_required(VERSION 3.24)

# ─── glad and glfw ───────────────────────────────────────────────────────────
if(ENGINE_INTEGRATION_GLFW_GLAD)

message(STATUS "GLFW/GLAD integration library selected")


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)

get_property(GLAD_LIB_NAME GLOBAL PROPERTY GLAD_LIB_NAME)

# GLFW
include(FetchContent)
FetchContent_Declare(
		glfw
		GIT_REPOSITORY https://github.com/glfw/glfw.git
		GIT_TAG        3.3.9
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

set(INTEGRATION_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INTEGRATION_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${ENGINE_PLATFORM_INTEGRATION_TARGET} OBJECT
	${INTEGRATION_SRC_DIR}/glad_texture_handle.cpp
	${INTEGRATION_SRC_DIR}/glad_texture_context.cpp
	${INTEGRATION_SRC_DIR}/glad_model_handle.cpp
	${INTEGRATION_SRC_DIR}/glad_model_context.cpp
	${INTEGRATION_SRC_DIR}/glad_shader_helper.cpp
	${INTEGRATION_SRC_DIR}/glad_shader_handle.cpp
	${INTEGRATION_SRC_DIR}/glad_shader_context.cpp
	${INTEGRATION_SRC_DIR}/glad_draw_context.cpp
	${INTEGRATION_SRC_DIR}/glad_renderer_context.cpp
	${INTEGRATION_SRC_DIR}/glad_renderer.cpp
	${INTEGRATION_SRC_DIR}/glfw_window_context.cpp
	${INTEGRATION_SRC_DIR}/glfw_input_context.cpp
	${INTEGRATION_SRC_DIR}/gg_context_manager.cpp
	${INTEGRATION_SRC_DIR}/glfw_window.cpp
	${INTEGRATION_SRC_DIR}/glfw_input.cpp
)

target_include_directories(${ENGINE_PLATFORM_INTEGRATION_TARGET} PUBLIC ${INTEGRATION_INC_DIR})
target_precompile_headers(${ENGINE_PLATFORM_INTEGRATION_TARGET} PUBLIC ${INTEGRATION_INC_DIR}/gg_integration.hpp)

target_link_libraries(${ENGINE_PLATFORM_INTEGRATION_TARGET} PUBLIC ${GLAD_LIB_NAME} glfw ${ENGINE_TARGET})
add_dependencies(${ENGINE_PLATFORM_INTEGRATION_TARGET} ${GLAD_LIB_NAME} glfw ${ENGINE_TARGET})

set_property(GLOBAL PROPERTY ENGINE_PLATFORM_INTEGRATION_LINKED 1)

endif()