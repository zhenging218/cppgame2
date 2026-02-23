cmake_minimum_required(VERSION 3.24)

# ─── Raylib ──────────────────────────────────────────────────────────────────
if("${INTEGRATION_API}" STREQUAL "GLFW_GLAD")

find_package(OpenGL REQUIRED)

include(FetchContent)
FetchContent_Declare(
		glad
		GIT_REPOSITORY https://github.com/Dav1dde/glad.git
		GIT_TAG        v2.0.8
)
FetchContent_MakeAvailable(glad)

# GLFW
FetchContent_Declare(
		glfw
		GIT_REPOSITORY https://github.com/glfw/glfw.git
		GIT_TAG        3.3.9
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)


set(ENGINE_INC_DIR ${CMAKE_SOURCE_DIR}/engine/include)

set(INTEGRATION_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INTEGRATION_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(gg_integration STATIC
	${INTEGRATION_SRC_DIR}/glfw_window_context.cpp
	${INTEGRATION_SRC_DIR}/glfw_window.cpp
)

target_include_directories(gg_integration PUBLIC ${ENGINE_INC_DIR} ${INTEGRATION_INC_DIR})
target_precompile_headers(gg_integration PUBLIC ${INTEGRATION_INC_DIR}/gg_integration.hpp)

target_link_libraries(gg_integration PUBLIC glad glfw OpenGL::GL engine)

set(CPP_GAME_INTEGRATION gg_integration PARENT_SCOPE)
set(CPP_GAME_INTEGRATION_NOT_LINKED 0 PARENT_SCOPE)

endif()