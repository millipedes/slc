cmake_minimum_required(VERSION 3.5)
project(slc)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")
set(SRC_FILES
  ${SRC_DIR}/canvas/canvas.c
  ${SRC_DIR}/evaluation/bool.c
  ${SRC_DIR}/evaluation/double.c
  ${SRC_DIR}/evaluation/evaluation.c
  ${SRC_DIR}/evaluation/integer.c
  ${SRC_DIR}/evaluation/string.c
  ${SRC_DIR}/parsing/parsing.c
)

include_directories(
  ${SRC_DIR}
)

add_executable(slc ${SRC_FILES} src/main/main.c)

find_package(PNG REQUIRED)

target_link_libraries(slc PNG::PNG m)

option(BUILD_TESTS "Build Test Suite" ON)

if(BUILD_TESTS)
  enable_testing()
  set(TEST_SRC_FILES
    ${TEST_DIR}/parsing.cpp
    ${TEST_DIR}/evaluation.cpp
    ${TEST_DIR}/test_helper.cpp
  )
  add_executable(tests ${TEST_SRC_FILES} test/main.cpp)
  target_link_libraries(tests ${SRC_FILES} gtest gtest_main pthread PNG::PNG m)
endif()
