#ifndef BINARYLINALG_MATRIX_H
#define BINARYLINALG_MATRIX_H

/**
 * @file matrix.h
 * <b>Notes on matrix.h</b>:
 *	- a vector is of type `bool *` and is a pointer to an array of `bool`s
 *	- a matrix is of type `bool **`: it is a pointer to an array of vectors, which are the rows of matrix
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "utils.h"
#ifdef __cplusplus
}
#endif


size_t position_in_array(size_t* array, size_t array_size, size_t element);


void print_matrix(const size_t num_rows, const size_t num_columns, bool** matrix);


void print_vector(const size_t num_rows, bool* vector);


/**
 * Element-wise 'add' `row_a` to `row_b` where 'add' means taking the exclusive or (XOR) of two `bool`s.
 * (`row_a` remains unchanged.)
 */
void add_row(const size_t num_rows, const size_t num_columns, const size_t row_a, const size_t row_b, bool **matrix);


void swap_rows(const size_t num_rows, const size_t row_a, const size_t row_b, bool **matrix);


/* Bring the left upper block of size `max_row` x `max_column` of a matrix into Row-Reduced Echelon Form (RREF).
 * TODO is the following correct??? To bring the entire matrix into RREF, use `max_row = num_rows - 1` and `max_column = num_columns - 1`.
 */
void bring_into_rref(const size_t num_rows, const size_t num_columns, const size_t max_row, const size_t max_column, bool **matrix);


#endif // BINARYLINALG_MATRIX_H
