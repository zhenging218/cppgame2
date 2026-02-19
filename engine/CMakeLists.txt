cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SXX_STANDARD REQUIRED True)

set(ENGINE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENGINE_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(ENGINE_MEMORY_SRCS
	${ENGINE_SRC_DIR}/memory/memory_control_block.cpp
	${ENGINE_SRC_DIR}/memory/reference_counter.cpp
	${ENGINE_SRC_DIR}/memory/type_descriptor.cpp
)

set(ENGINE_MATH_SRCS
	${ENGINE_SRC_DIR}/maths/vector2.cpp
	${ENGINE_SRC_DIR}/maths/vector3.cpp
	${ENGINE_SRC_DIR}/maths/vector4.cpp
	${ENGINE_SRC_DIR}/maths/quaternion.cpp
	${ENGINE_SRC_DIR}/maths/matrix2x2.cpp
	${ENGINE_SRC_DIR}/maths/matrix3x3.cpp
	${ENGINE_SRC_DIR}/maths/matrix4x4.cpp
	${ENGINE_SRC_DIR}/maths/triangle.cpp
	${ENGINE_SRC_DIR}/maths/rectangle_2d.cpp
	${ENGINE_SRC_DIR}/maths/transform.cpp
	${ENGINE_SRC_DIR}/maths/math_helper.cpp
)

set(ENGINE_ECS_SRCS
	${ENGINE_SRC_DIR}/ecs/enum_scene_state.cpp
	${ENGINE_SRC_DIR}/ecs/component.cpp
	${ENGINE_SRC_DIR}/ecs/game_object.cpp
	${ENGINE_SRC_DIR}/ecs/scene.cpp
	${ENGINE_SRC_DIR}/ecs/scene_manager.cpp
)

set(ENGINE_GRAPHICS_SRCS
	${ENGINE_SRC_DIR}/graphics/colour.cpp
	${ENGINE_SRC_DIR}/graphics/texture_handle.cpp
	${ENGINE_SRC_DIR}/graphics/shader_handle.cpp
	${ENGINE_SRC_DIR}/graphics/material.cpp
	${ENGINE_SRC_DIR}/graphics/renderable.cpp
	${ENGINE_SRC_DIR}/graphics/enum_camera_mode.cpp
	${ENGINE_SRC_DIR}/graphics/camera.cpp
	${ENGINE_SRC_DIR}/graphics/camera_2d.cpp
	${ENGINE_SRC_DIR}/graphics/triangle_primitive.cpp
	${ENGINE_SRC_DIR}/graphics/renderer.cpp
)

set(ENGINE_PLATFORM_SRCS
	${ENGINE_SRC_DIR}/platform/time.cpp
	${ENGINE_SRC_DIR}/platform/window.cpp
	${ENGINE_SRC_DIR}/platform/input.cpp
)

set(ENGINE_INTEGRATION_SRCS
		${ENGINE_SRC_DIR}/integration/window_context.cpp
		${ENGINE_SRC_DIR}/integration/renderer_context.cpp
		${ENGINE_SRC_DIR}/integration/draw_context.cpp
)

add_library(engine STATIC
	${ENGINE_MEMORY_SRCS}
	${ENGINE_MATH_SRCS}
	${ENGINE_ECS_SRCS}
	${ENGINE_GRAPHICS_SRCS}
	${ENGINE_PLATFORM_SRCS}
	${ENGINE_INTEGRATION_SRCS}
)

target_include_directories(engine PUBLIC ${ENGINE_INC_DIR})
target_precompile_headers(engine PUBLIC ${ENGINE_INC_DIR}/engine.hpp)

set(CPP_GAME_ENGINE engine PARENT_SCOPE)
set(CPP_GAME_ENGINE_NOT_LINKED 0 PARENT_SCOPE)