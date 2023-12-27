cmake_minimum_required(VERSION 3.9)

# Set a name and a version number for your project:
project(binarylinalg VERSION 0.0.1 LANGUAGES C CXX)

# Initialize some default paths
include(GNUInstallDirs)


# compile the library
add_subdirectory(src)

# tests
add_subdirectory(tests)

enable_testing()
add_test(NAME extend-check-matrix COMMAND test_extend_check_matrix)
add_test(NAME solve-linear-system COMMAND test_solve_linear_system)


#install(
#  TARGETS binarylinalg
#  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)


#install(
#  DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)
#
#include(FeatureSummary)
#feature_summary(WHAT ALL)
