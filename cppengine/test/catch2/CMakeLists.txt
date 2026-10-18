cmake_minimum_required(VERSION 3.24)

message(STATUS "preparing catch2 library for test target")
set(CATCH_2_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CATCH_2_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CATCH_2_TARGET_SRCS
    ${CATCH_2_SRC_DIR}/catch_amalgamated.cpp
)
add_library(catch2 ${CATCH_2_TARGET_SRCS})
target_include_directories(catch2 PUBLIC ${CATCH_2_INC_DIR})

set_property(GLOBAL PROPERTY TEST_SUITE_NAME catch2)
set_property(GLOBAL PROPERTY TEST_SUITE_LINKED 1)
