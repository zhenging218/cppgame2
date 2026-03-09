cmake_minimum_required(VERSION 3.24)

enable_language(C)

find_package(OpenGL REQUIRED)

set(GLAD_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLAD_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(glad STATIC ${GLAD_SRC_DIR}/glad/gl.cpp)
target_include_directories(glad PUBLIC ${GLAD_INC_DIR})
target_link_libraries(glad PUBLIC OpenGL::GL)

set_property(GLOBAL PROPERTY GLAD_LIB_NAME glad)