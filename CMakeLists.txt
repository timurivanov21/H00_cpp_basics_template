cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(H00_cpp_basics)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tasks_lib src/tasks.cpp include/tasks.hpp)
target_include_directories(tasks_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

include_directories(include)

# executables
add_executable(main main.cpp)
target_link_libraries(main PUBLIC tasks_lib)

# dependencies
add_subdirectory(contrib)

# tests
add_subdirectory(tests)