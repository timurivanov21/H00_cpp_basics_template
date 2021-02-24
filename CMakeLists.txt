# This is the top-level CMakeLists.txt file

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(H00_cpp_basics)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# create static library
add_library(tasks_lib src/tasks.cpp include/tasks.hpp)
target_include_directories(tasks_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# executables
add_executable(main main.cpp)
target_link_libraries(main PRIVATE tasks_lib)

# dependencies
add_subdirectory(contrib)

# tests
enable_testing()
add_subdirectory(tests)