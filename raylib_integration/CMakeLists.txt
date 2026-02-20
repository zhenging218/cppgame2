cmake_minimum_required(VERSION 3.24)

# ─── Raylib ──────────────────────────────────────────────────────────────────
if("${INTEGRATION_API}" STREQUAL "RAYLIB")

include(FetchContent)
FetchContent_Declare(
		raylib
		GIT_REPOSITORY  https://github.com/raysan5/raylib.git
		GIT_TAG         5.5
)
FetchContent_MakeAvailable(raylib)


set(ENGINE_INC_DIR ${CMAKE_SOURCE_DIR}/engine/include)

set(INTEGRATION_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INTEGRATION_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(raylib_integration STATIC
	${INTEGRATION_SRC_DIR}/raylib_window.cpp
	${INTEGRATION_SRC_DIR}/raylib_window_context.cpp
	${INTEGRATION_SRC_DIR}/raylib_input.cpp
	${INTEGRATION_SRC_DIR}/raylib_input_context.cpp
	${INTEGRATION_SRC_DIR}/raylib_renderer.cpp
	${INTEGRATION_SRC_DIR}/raylib_texture_context.cpp
	${INTEGRATION_SRC_DIR}/raylib_shader_handle.cpp
	${INTEGRATION_SRC_DIR}/raylib_shader_context.cpp
	${INTEGRATION_SRC_DIR}/raylib_renderer_context.cpp
	${INTEGRATION_SRC_DIR}/raylib_draw_context_2d.cpp
)

target_include_directories(raylib_integration PUBLIC ${ENGINE_INC_DIR} ${INTEGRATION_INC_DIR})
target_precompile_headers(raylib_integration PUBLIC ${INTEGRATION_INC_DIR}/raylib_integration.hpp)

target_link_libraries(raylib_integration PUBLIC raylib engine)
target_compile_definitions(raylib_integration PUBLIC RAYLIB_STATIC)

set(CPP_GAME_INTEGRATION raylib_integration PARENT_SCOPE)
set(CPP_GAME_INTEGRATION_NOT_LINKED 0 PARENT_SCOPE)

endif()