# Include testing CMake package.
# Tests can be launched by `ctest -VV` command.
include(CTest)

enable_testing()

# Include Catch2 cmake helper functions
include(${PROJECT_SOURCE_DIR}/contrib/Catch2/contrib/Catch.cmake)

add_executable(run_tests runner_tests.cpp tasks_tests.cpp)

target_link_libraries(run_tests PUBLIC tasks_lib)
target_link_libraries(run_tests PRIVATE Catch2::Catch2)

catch_discover_tests(run_tests EXTRA_ARGS -r compact)