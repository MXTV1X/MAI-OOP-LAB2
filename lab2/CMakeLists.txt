cmake_minimum_required(VERSION 3.10)
project(oop_labs)

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_library(Decimal STATIC src/lab2.cpp)

add_executable(RES main.cpp)

target_link_libraries(RES Decimal)

enable_testing()

add_executable(tests test/test.cpp)
target_link_libraries(tests Decimal gtest_main)