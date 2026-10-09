cmake_minimum_required(VERSION 3.16)

# Name CMake prints for this project. The executable and test names below stay
# the same if this project name changes.
project(cicd_autograder LANGUAGES CXX)

# C++ standard for the program and the tests. The sources are written for C++17.
# Change the number only when the sources use that standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Required before add_test(). Removing this makes CTest report that no tests ran.
enable_testing()

# Warning rubric applied to every target. -Werror makes a compiler warning fail
# the build, which the workflow reports as a failed grade. Add a flag to tighten
# the rubric, or remove -Werror to keep warnings non-fatal.
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Code under test. Add a new assignment source to this list when the program grows.
add_library(grade STATIC src/grade.cpp)
target_include_directories(grade PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Command-line program. The CLI tests invoke this executable.
add_executable(grader src/main.cpp)
target_link_libraries(grader PRIVATE grade)

# Rubric executable. Each failed check returns a non-zero status.
add_executable(grade_tests tests/test_grade.cpp)
target_link_libraries(grade_tests PRIVATE grade)

# Unit rubric. `ctest -R grade_unit` runs this check alone.
add_test(NAME grade_unit COMMAND grade_tests)

# CLI rubric for a passing score. The test passes when stdout matches every pattern.
add_test(NAME grade_cli_pass COMMAND grader 8 10)
set_tests_properties(grade_cli_pass PROPERTIES PASS_REGULAR_EXPRESSION "80%;B;pass")

# CLI rubric for a failing score. The test passes when stdout matches every pattern.
add_test(NAME grade_cli_fail COMMAND grader 5 10)
set_tests_properties(grade_cli_fail PROPERTIES PASS_REGULAR_EXPRESSION "50%;F;fail")

# CLI rubric for a bad invocation. WILL_FAIL expects the program to exit non-zero.
add_test(NAME grade_cli_usage COMMAND grader)
set_tests_properties(grade_cli_usage PROPERTIES WILL_FAIL TRUE)
