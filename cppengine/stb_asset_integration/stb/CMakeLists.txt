cmake_minimum_required(VERSION 3.24)

enable_language(C)

set(STB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(STB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(stb STATIC ${STB_SRC_DIR}/stb_image.cpp)
target_include_directories(stb PUBLIC ${STB_INC_DIR})
set_property(GLOBAL PROPERTY STB_LIB_NAME stb)