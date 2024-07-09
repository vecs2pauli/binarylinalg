CHANGELOG
=========

2024-07-09 (0.0.2)
------------------
- fixed bug: failure when solving a linear system of equations when the matrix is not full rank. Also added tests that cover the bug fix
- added and updated CMakeLists.txt files, in order to work to check for memory errors and to include running examples when testing
- fixed memory leak in function `is_row_in_span_of_other_rows` and in the file `extend_check_matrix.c`
- code prettyfying: use `const` instead of `#define` for defining some constants. This required replaced array allocations in examples and test with dynamic memory allocation in case the array size was defined with `const`
- corrections in documentation


2023-12-27 (0.0.1)
------------------
- release
