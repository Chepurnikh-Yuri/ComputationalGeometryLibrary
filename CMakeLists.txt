cmake_minimum_required(VERSION 3.10)
project(ComputationalGeometryLibrary)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(ComputationalGeometryLibrary INTERFACE)
target_include_directories(ComputationalGeometryLibrary INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/data_structures
)

# gtest
add_subdirectory(third_party/googletest)

# test
enable_testing()

add_executable(LibTest test/test.cpp test/rtree.cpp)
target_link_libraries(LibTest PRIVATE ComputationalGeometryLibrary gtest_main)

add_test(NAME LibTest COMMAND LibTest)