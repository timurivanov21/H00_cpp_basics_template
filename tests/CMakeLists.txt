# ctest -VV
include(CTest)

# Catch2 cmake helper functions
include(${PROJECT_SOURCE_DIR}/contrib/Catch2/contrib/Catch.cmake)

set(TARGET_NAME run_tests)

add_executable(${TARGET_NAME} runner_tests.cpp tasks_tests.cpp)

target_link_libraries(${TARGET_NAME} PUBLIC tasks_lib)
target_link_libraries(${TARGET_NAME} PUBLIC Catch2::Catch2)

# discover tests for CTest
catch_discover_tests(${TARGET_NAME} EXTRA_ARGS -r compact -D 120)