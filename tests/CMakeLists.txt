

add_executable(test_extend_check_matrix test_extend_check_matrix.c)
target_link_libraries(test_extend_check_matrix PUBLIC binarylinalg)


add_executable(test_solve_linear_system test_solve_linear_system.c)
target_link_libraries(test_solve_linear_system PUBLIC binarylinalg)



# allow user to run tests with `make test` or `ctest`
#catch_discover_tests(tests)
