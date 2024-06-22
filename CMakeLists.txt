cmake_minimum_required(VERSION 3.5)
project(slc)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")
set(SRC_FILES
  ${SRC_DIR}/parsing/parsing.c
)

include_directories(
  ${SRC_DIR}
)

add_executable(slc ${SRC_FILES} src/main/main.c)

option(BUILD_TESTS "Build Test Suite" OFF)

if(BUILD_TESTS)
  enable_testing()
  add_executable(tests test/main.cpp)
  target_link_libraries(tests ${SRC_FILES} gtest gtest_main pthread)
endif()
