cmake_minimum_required(VERSION 3.5)
project(slc)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")
set(SRC_FILES
  ${SRC_DIR}/evaluation/bool.c
  ${SRC_DIR}/evaluation/canvas.c
  ${SRC_DIR}/evaluation/coordinate.c
  ${SRC_DIR}/evaluation/double.c
  ${SRC_DIR}/evaluation/draw_stack.c
  ${SRC_DIR}/evaluation/ellipse.c
  ${SRC_DIR}/evaluation/evaluation.c
  ${SRC_DIR}/evaluation/evaluation_drawing.c
  ${SRC_DIR}/evaluation/evaluation_types.c
  ${SRC_DIR}/evaluation/integer.c
  ${SRC_DIR}/evaluation/line.c
  ${SRC_DIR}/evaluation/rectangle.c
  ${SRC_DIR}/evaluation/string.c
  ${SRC_DIR}/evaluation/symbol_table.c
  ${SRC_DIR}/io/default_output_file.c
  ${SRC_DIR}/io/read_evaluate_file.c
  ${SRC_DIR}/parsing/parsing.c
  ${SRC_DIR}/parsing/parsing_ds.c
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
    ${TEST_DIR}/drawing_test.cpp
  )
  add_executable(tests ${TEST_SRC_FILES} test/main.cpp)
  target_link_libraries(tests ${SRC_FILES} gtest gtest_main pthread PNG::PNG m)
endif()
