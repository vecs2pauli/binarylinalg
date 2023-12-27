#ifndef BINARYLINALG_EXTENDCHECKMATRIX_H
#define BINARYLINALG_EXTENDCHECKMATRIX_H

/**
 * @file extend_check_matrix.h
 * This file contains functionality to work with a "check matrix", which
 * is a binary \f$k\f$ x \f$2n\f$ matrix with \f$k\leq n\f$, such that:
 * - the matrix is full rank
 * - each pair of rows `v` and `w` should have symplectic inner product \f$\sum_{m=1}^{2n} v_m \cdot w_n \f$ equal to zero, where \f$\cdot\f$ indicates binary multiplication
 *
 * <b> Typical example usage:</b>
 * \include example_extend_check_matrix.c
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
#include "solve_linear_system.h"
#ifdef __cplusplus
}
#endif

/**
 * Computes the symplectic inner product between two rows of a binary matrix `check_matrix`.
 * The symplectic inner product between two binary vectors `v` and `w` of length \f$2n\f$ is defined as \f$\sum_{m=1}^{2n} v_m \cdot w_n \f$.
 * `check_matrix` has dimensions `num_rows` x `2 * num_qubits`.
 *
 * @returns `true` if `row_a` and `row_b` have symplectic inner product one, and `false` if the inner product is zero
 */
bool do_rows_commute(const size_t row_a, const size_t row_b, const size_t num_rows, const size_t num_qubits, bool** check_matrix);


/**
 * Checks if the specific row with index `row_under_question` of `scratch_matrix` can be written as sum of a subset of the rows with indices `0, 1, 2, ..., row_under_question - 1`.
 * Leaves `scratch_matrix` unchanged.
 *
 */
bool is_row_in_span_of_other_rows(const size_t row_under_question, const size_t num_columns, bool** scratch_matrix);


/**
 * Extends a check_matrix of dimensions `num_rows` x \f$2 \cdot\f$`num_qubits`,
 * to a check matrix with dimensions `num_qubits` x \f$2 \cdot\f$`num_qubits`.
 *
 * @pre `extended_check_matrix` has dimensions `num_qubits` x \f$2 \cdot\f$`num_qubits`.
 * The last `num_qubits - num_rows` will be overwritten.
 *
 */
void extend_rref_check_matrix(const size_t num_rows, const size_t num_qubits, bool** extended_check_matrix);



#endif // BINARYLINALG_EXTENDCHECKMATRIX_H
