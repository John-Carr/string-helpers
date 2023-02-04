cmake_policy(SET CMP0048 NEW)
project(AddrHelpers VERSION 1.0.0)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(GCOV_PATH gcov)
if(NOT GCOV_PATH)
    message(FATAL_ERROR "Code coverage analysis requires gcov!")
endif()

add_subdirectory(inc)
enable_testing()
add_subdirectory(test)
