cmake_minimum_required(VERSION 3.24)

# ─── glad and glfw ───────────────────────────────────────────────────────────
if("${INTEGRATION_API}" STREQUAL "GLFW_GLAD")

set(GLAD_LIB_NAME)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)

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

add_library(gg_integration OBJECT
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

target_include_directories(gg_integration PUBLIC ${INTEGRATION_INC_DIR})
target_precompile_headers(gg_integration PUBLIC ${INTEGRATION_INC_DIR}/gg_integration.hpp)

target_link_libraries(gg_integration PUBLIC ${GLAD_LIB_NAME} glfw engine)
add_dependencies(gg_integration ${GLAD_LIB_NAME} glfw engine)

set(CPP_GAME_INTEGRATION gg_integration PARENT_SCOPE)
set(CPP_GAME_INTEGRATION_NOT_LINKED 0 PARENT_SCOPE)

endif()