#ifndef BINARYLINALG_SOLVELINEARSYSTEM_H_
#define BINARYLINALG_SOLVELINEARSYSTEM_H_

/**
 * @file solve_linear_system.h
 * This file contains functionality to solve a binary system of equations.
 *
 * <b> Typical example usage:</b>
 * \include example_solve_linear_system.c
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "utils.h"
#include "matrix.h"
#ifdef __cplusplus
}
#endif


/**
 * Fills the first row of `solutions` with the single solution to the inhomogeneous equation M*v=b,
 * where M is a matrix and v and b vectors.
 * Here M consists of the first `num_columns - 1` columns of `matrix` and b is the last column of 'matrix'.
 * @pre `matrix` is in row-reduced echelon form (except for the last column)
 * @pre the first row of `solutions` is fully filled with `false` entries
 * @returns `false` if there are no solutions, and `true` otherwise
 */

bool single_solution_from_rref(const size_t num_rows, const size_t num_columns, bool **matrix, bool **solutions);

/**
 * Fills the rows of 'solutions', starting at the second row, with the single solution to the homogeneous equation M*v=0.
 * Here, M consists of the first 'num_columns-1' columns of 'matrix' and b is the last column of 'matrix'
 * @pre `matrix` is in row-reduced echelon form (except for the last column)
 * fills `solutions`
 * @returns dimension of solution space
 */
size_t solutions_from_rref(const size_t num_rows, const size_t num_columns, const size_t num_variables, bool **matrix, bool **solutions);

void allocate_and_fill_solutions_template(const size_t num_variables, bool **solutions);
void reset_solutions_template(const size_t num_variables, bool **solutions);
void tear_down_solutions_template(const size_t num_variables, bool **solutions);


#endif //BINARYLINALG_SOLVELINEARSYSTEM_H_
