cmake_minimum_required(VERSION 3.24)

message(STATUS "configuring engine test suite ${PROJECT_NAME}")

set(TEST_TARGET_NAME ${PROJECT_NAME}_test)

set(TEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TEST_TARGET_SRCS
    ${TEST_SRC_DIR}/bootstrap_test.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/catch2)

get_property(TEST_SUITE_LINKED GLOBAL PROPERTY TEST_SUITE_LINKED)

if(NOT TEST_SUITE_LINKED)
message(FATAL_ERROR "test suite backing library dependency could not be linked, please check settings")
else()
get_property(TEST_SUITE_NAME GLOBAL PROPERTY TEST_SUITE_NAME)
add_executable(${TEST_TARGET_NAME} ${TEST_TARGET_SRCS})
target_include_directories(${TEST_TARGET_NAME} PRIVATE ${TEST_INC_DIR})
target_link_libraries(${TEST_TARGET_NAME} PRIVATE ${PROJECT_NAME} ${TEST_SUITE_NAME})
add_dependencies(${TEST_TARGET_NAME} ${PROJECT_NAME} ${TEST_SUITE_NAME})
endif()