cmake_minimum_required(VERSION 3.9)

# Set a name and a version number for your project:
project(binarylinalg VERSION 0.0.2 LANGUAGES C CXX)

# Initialize some default paths
include(GNUInstallDirs)


# compile the library
add_subdirectory(src)

# tests
add_subdirectory(tests)

include(CTest)
add_test(NAME extend-check-matrix COMMAND test_extend_check_matrix)
add_test(NAME solve-linear-system COMMAND test_solve_linear_system)

# examples
add_subdirectory(examples)

add_test(NAME example-extend-check-matrix COMMAND example_extend_check_matrix)
add_test(NAME example-solve-linear-system COMMAND example_solve_linear_system)