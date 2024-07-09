

add_executable(example_extend_check_matrix example_extend_check_matrix.c)
target_link_libraries(example_extend_check_matrix PUBLIC binarylinalg)


add_executable(example_solve_linear_system example_solve_linear_system.c)
target_link_libraries(example_solve_linear_system PUBLIC binarylinalg)



# allow user to run examples with `make example` or `cexample`
#catch_discover_examples(examples)
